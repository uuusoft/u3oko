/**
\file       mjpeg-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_vcodec_mjpg
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::codecs::vcodec_mjpg
{
MjpegImpl::MjpegImpl () :
  jpeg_buf_ (nullptr),
  size_jpeg_buf_ (0),
  hjpeg_ (nullptr)
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  simd_     = ::libs::helpers::sys::cpu::CpuExts::usual;
}


MjpegImpl::~MjpegImpl ()
{
  if (jpeg_buf_)
  {
    tjFree (jpeg_buf_);
    jpeg_buf_ = nullptr;
  }

  if (hjpeg_)
  {
    tjDestroy (hjpeg_);
    hjpeg_ = nullptr;
  }
}


void
MjpegImpl::set_codec_info_int (const syn::VideoCodecProp* cinfo)
{
  cinfo_.copy (cinfo);
}


void
MjpegImpl::get_codec_info_int (syn::VideoCodecProp* ret_info)
{
  ret_info->copy (&cinfo_);
}


void
MjpegImpl::set_cpu_int (::libs::helpers::sys::cpu::CpuExts optim)
{
}


void
MjpegImpl::init_int (const codec_gen::InfoGenCodec& info)
{
  info.check ();
  iinfo_ = info;

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  fx16_x8_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));
  fx8_x16_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  fhsl_to_rgb24_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CHSL2RgbAlg::val_key));

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  temp_buf_ = ibuf->create (0);
}


const syn::StatisticInfo&
MjpegImpl::get_statistic_info_int () const
{
  return statistic_;
}


void
MjpegImpl::reset_statistic_info_int ()
{
  statistic_.reset ();
}


void
MjpegImpl::update_coder (const unsigned long max_size)
{
  U3_LOG_DATA_DBG ("dlls::codecs::vcodec_mjpg::MjpegImpl::update_coder" + VTOLOG (max_size));

  if (!hjpeg_)
  {
    hjpeg_ = tjInitCompress ();
    U3_CHECK_TURBO_JPEG (hjpeg_, "tjInitCompress");
  }

  if (!jpeg_buf_ || max_size > size_jpeg_buf_)
  {
    if (jpeg_buf_)
    {
      tjFree (jpeg_buf_);
      jpeg_buf_ = nullptr;
    }

    jpeg_buf_      = tjAlloc (U3_CAST_INT32 (max_size));
    size_jpeg_buf_ = max_size;
  }
}


void
MjpegImpl::update_decoder ()
{
  if (hjpeg_)
  {
    return;
  }

  hjpeg_ = tjInitDecompress ();
  U3_CHECK_TURBO_JPEG (hjpeg_, "tjInitDecompress");
}
}   // namespace dlls::codecs::vcodec_mjpg
