/**
\file       buf-allocator.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_dbufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../dbufs-includes_int.hpp"

#include "buf-allocator.hpp"
#include "mmedia/utils/dbufs/video/impl/video-buf.hpp"

extern "C" BOOST_SYMBOL_EXPORT
  utils::dbufs::allocator::BufAllocator*
  create_dbufs_impl ()
{
  return utils::dbufs::allocator::BufAllocator::instance ();
}


namespace utils::dbufs::allocator
{
BufAllocator*
BufAllocator::instance ()
{
  static BufAllocator* impl (new BufAllocator ());   //  Никогда не удаляем.
  return impl;
}


BufAllocator::BufAllocator () :
  counter_alloc_bufs_ (0),
  counter_reuse_bufs_ (0)
{
}


BufAllocator::~BufAllocator ()
{
  clear ();
}


utils::dbufs::video::IVideoBuf::ptr
BufAllocator::create (IBufAllocator::size_type size)
{
  lock_type lock (mtx_);

  for (const utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    // буфер еще используется, пропускаем
    if (buf.use_count () > 1)
    {
      continue;
    }
    //  найден уже выделенный и уже не используемый клиентом буфер.
    bool size_ok = false;
    // оцениваем его пригодность по размеру - он должен быть достаточным и при этом не слишком большим
    if (size)
    {
      const auto _raw_buf = buf->get_raw_buf ();
      if (_raw_buf)
      {
        const auto  size_raw_buf = _raw_buf->get_buf_size ();
        const float _koeff_size   = size_raw_buf / U3_CAST_STATIC< float > (size);

        size_ok = _koeff_size >= 1.0f && _koeff_size <= 2.0f;
      }
    }

    if (0 == size || size_ok)
    {
      buf->set_flag (::utils::dbufs::BufFlags::empty, true);
      ++counter_reuse_bufs_;
      return buf;
    }
  }
  //  выделяем новый буфер.
  utils::dbufs::video::IVideoBuf::ptr _new (new utils::dbufs::video::impl::VideoBuf ());
  bufs_.push_back (_new);
  ++counter_alloc_bufs_;
  return _new;
}


void
BufAllocator::clear ()
{
  lock_type lock (mtx_);
  dump_state_int ();

  for (utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    U3_ASSERT (buf.use_count () <= 1);
    buf->set_flag (::utils::dbufs::BufFlags::empty, true);
    buf.reset ();
  }

  bufs_.clear ();
  counter_alloc_bufs_ = 0;
  counter_reuse_bufs_ = 0;
}


std::string
BufAllocator::dump_bufs_state ()
{
  lock_type lock (mtx_);
  return dump_state_int ();
}


std::string
BufAllocator::dump_state_int ()
{
  std::int64_t _all_mem        = 0;
  std::int64_t _use_mem        = 0;
  std::int64_t _count_use_bufs = 0;
  const auto   _count_all_bufs = bufs_.size ();

  for (const utils::dbufs::video::IVideoBuf::ptr& buf : bufs_)
  {
    auto _mem_buf = (*buf)[::utils::dbufs::MemVars::size_buf];
    if (buf.use_count () > 1)
    {
      _use_mem += _mem_buf;
      ++_count_use_bufs;
    }
    _all_mem += _mem_buf;
  }

  return std::to_string (_all_mem) + " bytes {" + std::to_string (_count_all_bufs) + "}, use " +
         std::to_string (_use_mem) + " {" + std::to_string (_count_use_bufs) + "} koeff " +
         std::to_string (U3_CAST_STATIC< float > (_use_mem) / (_all_mem ? _all_mem : 1));
}
}   // namespace utils::dbufs::allocator
