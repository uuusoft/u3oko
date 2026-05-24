/**
\file       imem-buf.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       11.08.2018
\project    u3_dbufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "dbufs-includes_int.hpp"
#include "imem-buf.hpp"

namespace utils::dbufs
{
IMemBuf::IMemBuf ()
{
}


IMemBuf::~IMemBuf ()
{
}


void
IMemBuf::ialloc (const mem_type& size)
{
  if (!raw_)
  {
    auto _imem = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ();
    raw_       = _imem->alloc (size);
  }

  U3_CHECK (raw_, "get empty raw_");
  if (raw_->get_buf_size () < size)
  {
    raw_->resize (size);
  }
}


void
IMemBuf::flush ()
{
  mem_vars_[MemVars::size_data] = 0;
  fragments_.clear ();
}


void
IMemBuf::set_mem_var_int (const MemVars& _type, mem_type _val)
{
  switch (_type)
  {
  case MemVars::size_data:
    if (_val > 0)
    {
      U3_CHECK (_val || raw_, "try set size_data to empty raw_");
      U3_CHECK (_val <= raw_->get_buf_size (), VTOLOG (_val) + VTOLOG (raw_->get_buf_size ()));
    }
    break;
  case MemVars::offset_data:
    U3_CHECK (_val < (*this)[MemVars::size_buf] || 0 == _val, "offset large size" + VTOLOG (_val) + VTOLOG ((*this)[MemVars::size_buf]));
    break;
  case MemVars::size_buf:
    U3_XLOG_ERROR ("try set size_buf" + VTOLOG (_val));
    return;
  default:
    break;
  }

  mem_vars_[_type] = _val;
}


IMemBuf::mem_type
IMemBuf::get_mem_var_int (const ::utils::dbufs::MemVars& _type) const
{
  switch (_type)
  {
  case MemVars::size_buf:
    return raw_ ? raw_->get_buf_size () : 0;
  default:
    break;
  }
  return mem_vars_[_type];
}


std::uint8_t*
IMemBuf::get_buf_int ()
{
  U3_ASSERT (raw_);
  return raw_->get ();
}


const std::uint8_t*
IMemBuf::get_cbuf_int () const
{
  U3_ASSERT (raw_);
  return raw_->get ();
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

  if (percent <= 0.0f)
  {
    mem_vars_[MemVars::size_data] = 0;
    return;
  }

  if (!src->raw_)
  {
    U3_XLOG_WARN ("try empty clone" + PTR_TOLOG (this));
    return;
  }

  ::libs::helpers::mem::u3copy (src->get_cbuf (), get_buf (), (*src)[MemVars::size_buf]);
  fragments_ = src->fragments_;
}


void
IMemBuf::swap_int (IBuf& isrc)
{
  IMemBuf& src = dynamic_cast< IMemBuf& > (isrc);
  if (this == &src)
  {
    U3_XLOG_WARN ("try swap itself" + PTR_TOLOG (this));
    return;
  }

  std::swap (raw_, src.raw_);
  std::swap (mem_vars_, src.mem_vars_);
  std::swap (fragments_, src.fragments_);
}
}   // namespace utils::dbufs
