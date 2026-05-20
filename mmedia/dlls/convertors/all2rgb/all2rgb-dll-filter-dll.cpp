/**
\file       all2rgb-dll-filter-dll.cpp
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
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::convertors::all2rgb
{
Filter::Filter ()
{
}


Filter::~Filter ()
{
}


void
Filter::load_int (
  ::libs::icore::impl::var1::obj::FilterInfo* info,
  const ::pugi::xml_named_node_iterator&      node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  rgb32_to_rgb24_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRGB32_RGB24Alg::val_key));
  yuy2_to_rgb24_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CYUY22RgbAlg::val_key));
  yuy2_to_y16_    = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CYUY22Y16Alg::val_key));
  nv21_to_rgb24_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CNV212RgbAlg::val_key));
  nv21_to_y16_    = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CNV212Y16Alg::val_key));
  ycb_to_rgb24_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::YCB2RgbAlg::val_key));
  scale_func_     = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CScaleNearestAlg::val_key));
  i420_to_rgb24_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::I420ToRgb24Alg::val_key));
  uyvy_to_rgb24_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CUYVY2RgbAlg::val_key));
  uyvy_to_y16_    = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CUYVY2Y16Alg::val_key));
}


bool
is_valid_format (const ::libs::helpers::uids::minor::id_val& buf_format)
{
  if (::libs::helpers::uids::minor::id_val::yuy2 != buf_format &&
      ::libs::helpers::uids::minor::id_val::yuyv != buf_format &&
      ::libs::helpers::uids::minor::id_val::uyvy != buf_format &&
      ::libs::helpers::uids::minor::id_val::nv21 != buf_format &&
      ::libs::helpers::uids::minor::id_val::ycb != buf_format &&
      ::libs::helpers::uids::minor::id_val::i420 != buf_format &&
      ::libs::helpers::uids::minor::id_val::rgb32 != buf_format)
  {
    U3_LOG_DATA_ERROR ("only {rgb24, rgb32, yuy2, yuyv, ycb, nv21, i420} formats accepted");
    return false;
  }
  return true;
}


void
Filter::transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info)
{
  prepare_transform (info);

  auto& ibuf = (*info.ibuf_);
  if (ibuf->get_flag (::libs::bufs::BufsFlags::empty))
  {
    //  Пустой буфер допустим, например если все преобразование происходит аппаратно.
    return;
  }

  auto sbuf = (*ibuf)[finfo_.rprops_->buf_.indx_sbuf_];
  auto dbuf = (*ibuf)[finfo_.rprops_->buf_.indx_dbuf_];
  if (!sbuf || !dbuf)
  {
    return;
  }
  if (sbuf->get_flag (utils::dbufs::BufFlags::empty))
  {
    return;
  }

  pbuf_->set_flag (::libs::bufs::BufsFlags::request2hsl, true);
  if (::libs::helpers::uids::minor::id_val::rgb24 == sbuf->get_format ())
  {
    // U3-TODO: restride allready
    return;
  }

  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  const auto buf_format = sbuf->get_format ();
  if (!is_valid_format (buf_format))
  {
    U3_LOG_DATA_ERROR ("invalid format recive " + ::libs::helpers::uids::helpers::get_readable_name (buf_format));
    return;
  }

  itransform ();
}


bool
Filter::is_result_mono (const ::libs::helpers::uids::minor::id_val& format) const
{
  //< see Filter::get_func_for_format
  const bool mono_support = format != ::libs::helpers::uids::minor::id_val::rgb32 && format != ::libs::helpers::uids::minor::id_val::rgb24;
  return finfo_.rprops_->strip_color_ && mono_support;
}


::libs::optim::io::hioptim*
Filter::get_func_for_format (const ::libs::helpers::uids::minor::id_val& format)
{
  const auto mono = is_result_mono (format);
  if (::libs::helpers::uids::minor::id_val::yuy2 == format ||
      ::libs::helpers::uids::minor::id_val::yuyv == format)
  {
    return mono ? &yuy2_to_y16_ : &yuy2_to_rgb24_;
  }
  if (::libs::helpers::uids::minor::id_val::ycb == format)
  {
    return mono ? &yuy2_to_y16_ : &ycb_to_rgb24_;
  }
  if (::libs::helpers::uids::minor::id_val::uyvy == format)
  {
    return mono ? &uyvy_to_y16_ : &uyvy_to_rgb24_;
  }
  if (::libs::helpers::uids::minor::id_val::nv21 == format)
  {
    return mono ? &nv21_to_y16_ : &nv21_to_rgb24_;
  }
  if (::libs::helpers::uids::minor::id_val::i420 == format)
  {
    return mono ? &nv21_to_y16_ : &i420_to_rgb24_;
  }
  if (::libs::helpers::uids::minor::id_val::rgb32 == format)
  {
    U3_CHECK (!mono, "result mono for rgb32");
    return &rgb32_to_rgb24_;
  }
  U3_LOG_DATA_ERROR ("unknown pixel format");
  return nullptr;
}


::libs::helpers::uids::minor::id_val
Filter::get_out_format_from_format (const ::libs::helpers::uids::minor::id_val& format)
{
  return is_result_mono (format) ? ::libs::helpers::uids::minor::id_val::y16 : ::libs::helpers::uids::minor::id_val::rgb24;
}


void
Filter::call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}
}   // namespace dlls::convertors::all2rgb
