/**
\file       bufs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       16.05.2016
\project    u3_bufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-bufs-includes_int.hpp"
#include "bufs.hpp"

namespace libs::bufs
{
Bufs::Bufs ()
{
  flags_.fill (false);
  flags_[BufsFlags::request2hsl] = true;
  set_flag (BufsFlags::empty, true);
}


void
Bufs::set_base_index (const syn::off_buf_type& indx)
{
  base_buf_index_ = indx;
}


syn::off_buf_type
Bufs::get_base_index () const
{
  return base_buf_index_;
}


void
Bufs::reset (bool only_indxs)
{
  if (!only_indxs)
  {
    for (auto& child : childs_)
    {
      auto& cbuf = child.second;
      cbuf->flush ();
    }
  }

  base_buf_index_ = utils::dbufs::video::consts::offs::raw;
  set_flag (BufsFlags::empty, true);
  flags_[BufsFlags::request2hsl] = true;
}


syn::IVideoBuf::raw_ptr
Bufs::operator[] (const syn::off_buf_type& indx)
{
  if (indx == ::utils::dbufs::video::consts::offs::invalid)
  {
    return nullptr;
  }

  auto& ret = childs_[indx];
  if (!ret)
  {
    auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ();
    ret       = ibuf->impl ()->create (0);
  }
  return ret.get ();
}


syn::IVideoBuf::craw_ptr
Bufs::operator[] (const syn::off_buf_type& indx) const
{
  if (indx == ::utils::dbufs::video::consts::offs::invalid)
  {
    return nullptr;
  }

  auto& ret = childs_[indx];
  if (!ret)
  {
    auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ();
    ret       = ibuf->impl ()->create (0);
  }
  return ret.get ();
}


void
Bufs::swap (Bufs& src)
{
  if (this == &src)
  {
    U3_ASSERT_SIGNAL ("failed");
    return;
  }

  std::swap (childs_, src.childs_);
  // std::swap( ichilds_, src.ichilds_ );
  std::swap (flags_, src.flags_);
  std::swap (base_buf_index_, src.base_buf_index_);
}


void
Bufs::clone (const Bufs& src)
{
  if (&src == this)
  {
    U3_ASSERT_SIGNAL ("failed");
    return;
  }

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ();

  childs_.clear ();

  for (auto& schild : src.childs_)
  {
    auto& dchild = childs_[schild.first];
    if (!schild.second)
    {
      continue;
    }

    dchild = ibuf->impl ()->create (schild.second->getraw_buf () ? schild.second->getraw_buf ()->get_data_size () : 0);
    dchild->clone (schild.second.get (), 100.0F);
  }

  // ichilds_ = src.ichilds_;
  flags_          = src.flags_;
  base_buf_index_ = src.base_buf_index_;
}


void
Bufs::set_buf (const syn::off_buf_type& indx, syn::IVideoBuf::ptr& buf)
{
  childs_[indx] = buf;
}


void
Bufs::set_flag (const BufsFlags& key, bool val)
{
  if (BufsFlags::empty != key)
  {
    flags_[key] = val;
    return;
  }

  auto base_buf = (*this)[get_base_index ()];
  if (!base_buf)
  {
    return;
  }

  base_buf->set_flag (::utils::dbufs::BufFlags::empty, val);
}


bool
Bufs::get_flag (const BufsFlags& key) const
{
  if (BufsFlags::empty != key)
  {
    return flags_[key];
  }

  auto base_buf = (*this)[get_base_index ()];
  if (!base_buf)
  {
    return true;
  }
  return base_buf->get_flag (::utils::dbufs::BufFlags::empty);
}


void
Bufs::enum_bufs (enum_bufs_func_type funct) const
{
  for (const auto& el : childs_)
  {
    funct (el.first, el.second);
  }
}
}   // namespace libs::bufs
