/**
\file       all2hsl-dll-filter-dll-ifilter.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_all2hsl
*/
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::convertors::all2hsl
{
void
Filter::load_int (
  ::libs::icore::impl::var1::obj::FilterInfo* info,
  const ::pugi::xml_named_node_iterator&      node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  fx8_to_x16_          = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  rgb24_to_hsl_        = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2HSLAlg::val_key));
  rgb24_to_l_fast_     = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2LAlg::val_key));
  rgb24_to_l_accurate_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2LAlg2::val_key));
  set_const_func_      = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CSetConstAlg::val_key));
  scale_func_          = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CScaleNearestAlg::val_key));
  flip_y_              = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
}


void
Filter::transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  auto& ibufs = (*info.ibuf_);
  if (ibufs->get_flag (::libs::bufs::BufsFlags::empty))
  {
    //  Пустой буфер допустим, например если все преобразование происходит аппаратно.
    return;
  }
  if (!ibufs->get_flag (::libs::bufs::BufsFlags::request2hsl))
  {
    return;
  }

  auto        indx_base_buf = ::utils::dbufs::video::consts::offs::raw;
  auto        base_buf      = (*ibufs)[indx_base_buf];
  const auto& format        = base_buf->get_format ();

  if (base_buf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    //  Требуется уточнение уже для непосредственного буфера источника. Пустой буфер допустим, например если все преобразование происходит аппаратно.
    return;
  }
  if (::libs::helpers::uids::minor::id_val::rgb24 != format && ::libs::helpers::uids::minor::id_val::y16 != format && ::libs::helpers::uids::minor::id_val::y8 != format)
  {
    U3_LOG_DATA_WRN ("unknow format for HSL convert, skip, indx=" + indx_base_buf + ", format=" + ::libs::helpers::uids::helpers::get_readable_name (format));
    return;
  }

  //  add offset for active data and corrected active data correct frame
  itransform ();
  pbuf_->set_flag (::libs::bufs::BufsFlags::request2hsl, false);
}


void
Filter::call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}
}   // namespace dlls::convertors::all2hsl
