/**
\file       all2rgb-dll-filter-dll-ifilter.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_all2rgb
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::convertors::all2rgb
{
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


auto
is_valid_format (const syn::id_val& buf_format) -> bool
{
  if (syn::id_val::yuy2 != buf_format &&
      syn::id_val::yuyv != buf_format &&
      syn::id_val::uyvy != buf_format &&
      syn::id_val::nv21 != buf_format &&
      syn::id_val::ycb != buf_format &&
      syn::id_val::i420 != buf_format &&
      syn::id_val::rgb32 != buf_format)
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
  if (syn::id_val::rgb24 == sbuf->get_format ())
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
    U3_LOG_DATA_ERROR ("invalid format recive " + ::libs::utility::uids::helpers::get_readable_name (buf_format));
    return;
  }

  itransform ();
}


void
Filter::call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}
}   // namespace dlls::convertors::all2rgb
