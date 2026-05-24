/**
\file       detect-move-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_move
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-move-includes_int.hpp"
#include "detect-move-info-filter-dll.hpp"
#include "detect-move-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::detectors::detect_move
{
Filter::Filter () :
  count_detects_ (0),
  time_first_detect_ (boost::posix_time::microsec_clock::universal_time ())
{
}


Filter::~Filter ()
{
}


void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim  = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();
  count_if_ge_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCountIfGEAlg::val_key));
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

  syn::IVideoBuf::raw_ptr psrc = (*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_];
  if (!psrc || psrc->get_flag (::utils::dbufs::BufFlags::empty))
  {
    return;
  }

  itransform (info);
}
}   // namespace dlls::detectors::detect_move
