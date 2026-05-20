/**
\file       clone-bufs-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_bufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-bufs-includes_int.hpp"
#include "bufs.hpp"

namespace libs::bufs
{
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

    dchild = ibuf->impl ()->create (schild.second->get_raw_buf () ? schild.second->get_raw_buf ()->get_data_size () : 0);
    dchild->clone (schild.second.get (), 100.0f);
  }

  // ichilds_ = src.ichilds_;
  flags_          = src.flags_;
  base_buf_index_ = src.base_buf_index_;
}
}   // namespace libs::bufs
