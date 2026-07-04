/**
\file       alloc-bufs-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.03.2022
\project    u3_bufs
*/
#include "libs-bufs-includes_int.hpp"
#include "alloc-bufs-funcs.hpp"

namespace libs::bufs
{
void
alloc_buf_by_indx (
  Bufs::raw_ptr            bufs,
  const syn::off_buf_type& indx,
  syn::IVideoBuf::raw_ptr  src)
{
  U3_ASSERT (bufs);
  syn::IVideoBuf::raw_ptr nbuf = (*bufs)[indx];
  U3_ASSERT (nbuf);

  if (!src || src->get_flag (::utils::dbufs::BufFlags::empty))
  {
    U3_XLOG_WARN ("try alloc buf from empty buf" + TOLOG (indx));
    return;
  }
  if (nbuf == src)
  {
    return;
  }
  if (!utils::dbufs::video::helpers::buf_dimension_equal (*nbuf, *src))
  {
    nbuf->clone (src, 0.0F);
  }
}
}   // namespace libs::bufs
