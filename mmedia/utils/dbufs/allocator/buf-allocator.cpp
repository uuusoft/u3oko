/**
\file       buf-allocator.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_dbufs
*/
#include "../dbufs-includes_int.hpp"
#include "buf-allocator.hpp"
#include "mmedia/utils/dbufs/video/impl/video-buf.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_dbufs_impl () -> utils::dbufs::allocator::IBufAllocator::raw_ptr
{
  return utils::dbufs::allocator::BufAllocator::instance ();
}


namespace utils::dbufs::allocator
{
auto
BufAllocator::instance () -> IBufAllocator::raw_ptr
{
  static auto impl = std::unique_ptr< BufAllocator, void (*) (BufAllocator*) > (new BufAllocator {}, [] (BufAllocator* obj) -> void { delete obj; });
  return impl.get ();
}


BufAllocator::~BufAllocator ()
{
  clear ();
}


auto
BufAllocator::create (IBufAllocator::size_buf_type size) -> utils::dbufs::video::IVideoBuf::ptr
{
  lock_type lock (mtx_);
  for (const utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    if (buf.use_count () > 1)
    {
      // буфер еще используется, пропускаем
      continue;
    }
    // найден уже выделенный и уже не используемый клиентом буфер
    // оцениваем его пригодность по размеру - он должен быть достаточным и при этом не слишком большим
    bool size_ok = false;
    if (size)
    {
      // пользователю важен размер буфера
      const auto raw_buf = buf->getraw_buf ();
      if (raw_buf)
      {
        const auto  sizeraw_buf = raw_buf->get_capacity ();
        const float koeff_size  = sizeraw_buf / U3_CAST_FLOAT (size);

        size_ok = koeff_size >= 1.0F && koeff_size <= 2.0F;
      }
    }
    // если пользователю не важен размер буфера или размер буфера достаточен для пользователя
    if (0 == size || size_ok)
    {
      buf->set_flag (::utils::dbufs::BufFlags::empty, true);
      ++counter_reuse_bufs_;
      U3_XLOG_DBG ("return reuse buf" + VTOLOG (counter_reuse_bufs_) + VTOLOG (bufs_.size ()) + PTR_TOLOG (buf.get ()));
      return buf;
    }
  }

  //  выделяем новый буфер.
  utils::dbufs::video::IVideoBuf::ptr newbuf (new utils::dbufs::video::impl::VideoBuf ());
  bufs_.emplace_back (newbuf);
  ++counter_alloc_bufs_;
  U3_XLOG_DBG ("return new buf" + VTOLOG (counter_alloc_bufs_) + VTOLOG (bufs_.size ()) + PTR_TOLOG (newbuf.get ()));
  return newbuf;
}


void
BufAllocator::clear ()
{
  lock_type lock (mtx_);
  U3_XLOG_DEV ("BufAllocator::clear::---->" + VTOLOG (bufs_.size ()));
  U3_XLOG_DEV (TOLOG (dump_state_int ()));

  for (utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    U3_CHECK_NT (buf.use_count () <= 1, PTR_TOLOG (buf.get ()) + VTOLOG (buf.use_count ()));
    buf->set_flag (::utils::dbufs::BufFlags::empty, true);
    buf.reset ();
  }

  bufs_.clear ();
  counter_alloc_bufs_ = 0;
  counter_reuse_bufs_ = 0;
  U3_XLOG_DEV ("BufAllocator::clear::<----");
}


auto
BufAllocator::dump_bufs_state () -> std::string
{
  lock_type lock (mtx_);
  return dump_state_int ();
}


auto
BufAllocator::dump_state_int () -> std::string
{
  std::int64_t all_mem        = 0;
  std::int64_t use_mem        = 0;
  std::int64_t count_use_bufs = 0;
  const auto   count_all_bufs = bufs_.size ();

  for (const utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    auto mem_buf = (*buf)[::utils::dbufs::MemVars::size_buf];
    if (buf.use_count () > 1)
    {
      use_mem += mem_buf;
      ++count_use_bufs;
    }
    all_mem += mem_buf;
  }

  return std::to_string (all_mem) + " bytes {" + std::to_string (count_all_bufs) + "}, use " +
         std::to_string (use_mem) + " {" + std::to_string (count_use_bufs) + "} koeff " +
         std::to_string (U3_CAST_FLOAT (use_mem) / (all_mem ? all_mem : 1));
}
}   // namespace utils::dbufs::allocator
