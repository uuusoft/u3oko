#pragma once
/**
\file       alloc-bufs-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       15.08.2018
\project    u3_bufs
*/

namespace libs::bufs
{
void alloc_buf_by_indx (
  Bufs::raw_ptr            bufs,
  const syn::off_buf_type& indx,
  syn::IVideoBuf::raw_ptr  src);
}   // namespace libs::bufs
