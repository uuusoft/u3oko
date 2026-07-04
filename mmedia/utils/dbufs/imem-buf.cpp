/**
\file       imem-buf.cpp
\author     Erashov Anton erashov2026@proton.me
\date       11.08.2018
\project    u3_dbufs
*/
#include "dbufs-includes_int.hpp"
#include "imem-buf.hpp"

namespace utils::dbufs
{
void
IMemBuf::ialloc (const mem_var_type& size)
{
  if (!raw_block_)
  {
    auto _imem = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ();
    raw_block_ = _imem->alloc (size);
  }

  U3_CHECK (raw_block_, "get empty raw_block_");
  if (raw_block_->get_capacity () < size)
  {
    raw_block_->resize (size);
  }
}


void
IMemBuf::flush ()
{
  mem_vars_[MemVars::size_data] = 0;
  fragments_.clear ();
}


void
IMemBuf::set_mem_var_int (const MemVars& type, mem_var_type val)
{
  switch (type)
  {
  case MemVars::size_data:
    if (val > 0)
    {
      U3_CHECK (val || raw_block_, "try set size_data to empty raw_block_");
      U3_CHECK (val <= raw_block_->get_capacity (), VTOLOG (val) + VTOLOG (raw_block_->get_capacity ()));
    }
    break;
  case MemVars::offset_data:
    U3_CHECK (val < (*this)[MemVars::size_buf] || 0 == val, "offset large size" + VTOLOG (val) + VTOLOG ((*this)[MemVars::size_buf]));
    break;
  case MemVars::size_buf:
    U3_XLOG_ERROR ("try set size_buf" + VTOLOG (val));
    return;
  default:
    break;
  }

  mem_vars_[type] = val;
}


auto
IMemBuf::get_mem_var_int (const ::utils::dbufs::MemVars& type) const -> IMemBuf::mem_var_type
{
  switch (type)
  {
  case MemVars::size_buf:
    return raw_block_ ? raw_block_->get_capacity () : 0;
  default:
    break;
  }
  return mem_vars_[type];
}


auto
IMemBuf::get_buf_int () -> std::uint8_t*
{
  U3_ASSERT (raw_block_);
  return raw_block_->get ();
}


auto
IMemBuf::get_cbuf_int () const -> const std::uint8_t*
{
  U3_ASSERT (raw_block_);
  return raw_block_->get ();
}


void
IMemBuf::clone_int (IBuf::craw_ptr isrc, float percent)
{
  auto src = dynamic_cast< IMemBuf::craw_ptr > (isrc);
  U3_ASSERT (src);
  if (this == src)
  {
    U3_XLOG_WARN ("try clone itself" + PTR_TOLOG (this));
    return;
  }

  mem_vars_[MemVars::offset_data] = (*src)[MemVars::offset_data];
  mem_vars_[MemVars::size_buf]    = (*src)[MemVars::size_buf];
  mem_vars_[MemVars::size_data]   = (*src)[MemVars::size_data];

  ialloc ((*src)[MemVars::size_buf]);

  if (percent <= 0.0F)
  {
    mem_vars_[MemVars::size_data] = 0;
    return;
  }

  if (!src->raw_block_)
  {
    U3_XLOG_WARN ("try empty clone" + PTR_TOLOG (this));
    return;
  }

  ::libs::utility::mem::u3copy (src->get_cbuf (), get_buf (), (*src)[MemVars::size_buf]);
  fragments_ = src->fragments_;
}


void
IMemBuf::swap_int (IBuf& isrc)
{
  auto& src = dynamic_cast< IMemBuf& > (isrc);
  if (this == &src)
  {
    U3_XLOG_WARN ("try swap itself" + PTR_TOLOG (this));
    return;
  }

  std::swap (raw_block_, src.raw_block_);
  std::swap (mem_vars_, src.mem_vars_);
  std::swap (fragments_, src.fragments_);
}
}   // namespace utils::dbufs
