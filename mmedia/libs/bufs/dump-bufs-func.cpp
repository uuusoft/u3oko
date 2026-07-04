/**
\file       dump-bufs-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.03.2022
\project    u3_bufs
*/
#include "libs-bufs-includes_int.hpp"
#include "dump-bufs-func.hpp"

namespace libs::bufs
{
void
dump (Bufs::craw_ptr bufs, bool only_filled)
{
  if (only_filled && bufs->get_flag (BufsFlags::empty))
  {
    return;
  }

  U3_ASSERT (bufs);

  bufs->enum_bufs (
    [only_filled] (const syn::off_buf_type& indx, const syn::IVideoBuf::cptr& buf) -> void {
      U3_ASSERT (buf);
      if (only_filled && (buf->get_flag (::utils::dbufs::BufFlags::empty) || buf->get_flag (::utils::dbufs::BufFlags::null)))
      {
        return;
      }
      //::utils::dbufs::video::helpers::dump (buf.get (), only_filled);
      return;
    });
}
}   // namespace libs::bufs
