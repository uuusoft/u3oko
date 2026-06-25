/**
\file       vgen-mops-vgen_mops.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2017
\project    u3_vgen_mops
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-includes_int.hpp"
#include "vgen-mops-info-filter-dll.hpp"
#include "vgen-mops-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_mops
{
void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
  impl_.init ();
  impl_.set_props (finfo_.rprops_);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  impl_.set_transform_info (transinfo_);
  impl_.itransform (id_obj_, *pbuf_);
  impl_.set_transform_info (nullptr);
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
}   // namespace dlls::gens::vgen_mops
