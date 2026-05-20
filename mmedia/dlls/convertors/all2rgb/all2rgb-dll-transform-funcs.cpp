/**
\file       all2rgb-dll-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    uuu_all2rgb
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"

namespace dlls::convertors::all2rgb
{
void
Filter::convert_bufs ()
{
  auto       base_buf  = (*pbuf_)[finfo_.rprops_->buf_.indx_sbuf_];
  const auto pixformat = base_buf->get_format ();
  auto       rcbuf     = (*pbuf_)[finfo_.rprops_->buf_.indx_dbuf_];
  auto       tempbuf   = (*pbuf_)[::utils::dbufs::video::consts::offs::temp1];

  ::libs::optim::io::MCallInfo      cinfo;
  ::libs::optim::mcalls::InfoMFunct tfunct;

  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (rcbuf, "rcbuf dlls::convertors::all2rgb"));
  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (tempbuf, "tbuf dlls::convertors::all2rgb"));

  tempbuf->set_format (get_out_format_from_format (pixformat));

  tfunct.pfunc_           = get_func_for_format (pixformat);
  tfunct.src_align_.px_x_ = tfunct.pfunc_->get_block_align_x ();
  tfunct.dst_align_.px_x_ = tfunct.pfunc_->get_block_align_x ();
  tfunct.src_align_.px_y_ = tfunct.pfunc_->get_block_align_y ();
  tfunct.dst_align_.px_y_ = tfunct.pfunc_->get_block_align_y ();

  if (!finfo_.rprops_->debug_skip_transform_)
  {
    pthreads_->mthreads_call (id_obj_, tfunct, cinfo, transinfo_->exptimes_);
    U3_LOG_DATA_DBG ("buf after all2rgb" + VTOLOG ((*tempbuf)[::utils::dbufs::MemVars::size_data]));
  }

  // rcbuf->c1lone( tempbuf, 100.0f );
  rcbuf->swap (*tempbuf);

  if (is_result_mono (pixformat))
  {
    (*pbuf_)[::utils::dbufs::video::consts::offs::hue]->flush ();
    (*pbuf_)[::utils::dbufs::video::consts::offs::sat]->flush ();
  }
}


void
Filter::itransform ()
{
  alloc_bufs ();
  alloc_temp_bufs ();
  convert_bufs ();
}
}   // namespace dlls::convertors::all2rgb
