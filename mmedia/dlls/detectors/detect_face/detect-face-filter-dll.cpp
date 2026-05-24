/**
\file       detect-face-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_face
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::detectors::detect_face
{
Filter::Filter () :
  hjpeg_ (nullptr),
  jpeg_buf_ (nullptr),
  size_jpeg_buf_ (0)
{
}


Filter::~Filter ()
{
  if (jpeg_buf_)
  {
    tjFree (jpeg_buf_);
    jpeg_buf_      = nullptr;
    size_jpeg_buf_ = 0;
  }

  if (hjpeg_)
  {
    tjDestroy (hjpeg_);
    hjpeg_ = nullptr;
  }
}


void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);

  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  // count_if_ge_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCountIfGEAlg::val_key));
  fx16_x8_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  temp_buf_ = ibuf->create (0);
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  //  add offset for active data and corrected active data correct frame
  itransform (info);
}
}   // namespace dlls::detectors::detect_face
