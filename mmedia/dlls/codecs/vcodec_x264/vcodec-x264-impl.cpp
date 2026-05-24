/**
\file       vcodec-x264-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_vcodec_x264
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "vcodec-x264-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::codecs::vcodec_x264
{
x264Impl::x264Impl ()
{
  pthreads_   = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  simd_       = ::libs::helpers::sys::cpu::CpuExts::usual;
  coder_impl_ = impls::FactoryH264Impl::get_impl ();
}


x264Impl::~x264Impl ()
{
}


void
x264Impl::set_codec_info_int (const syn::VideoCodecProp* cinfo)
{
  cinfo_.copy (cinfo);
  coder_impl_->destroy_coder ();

  if (coder_frame_info_.geom_dims_[::utils::dbufs::video::Dims::width] && coder_frame_info_.geom_dims_[::utils::dbufs::video::Dims::height])
  {
    coder_impl_->create_coder (cinfo_, coder_frame_info_);
  }
}


void
x264Impl::get_codec_info_int (syn::VideoCodecProp* ret_info)
{
  ret_info->copy (&cinfo_);
}


void
x264Impl::set_cpu_int (::libs::helpers::sys::cpu::CpuExts optim)
{
}


void
x264Impl::init_int (const codec_gen::InfoGenCodec& info)
{
  info.check ();
  iinfo_ = info;

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  fx16_x8_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));
  fx8_x16_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  fhsl_to_rgb24_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CHSL2RgbAlg::val_key));
  i420_to_rgb24_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::I420ToRgb24Alg::val_key));

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  src_buf_  = ibuf->create (0);
}


const ::dlls::codecs::codec_gen::StatisticInfo&
x264Impl::get_statistic_info_int () const
{
  return statistic_;
}


void
x264Impl::reset_statistic_info_int ()
{
  statistic_.reset ();
}
}   // namespace dlls::codecs::vcodec_x264
