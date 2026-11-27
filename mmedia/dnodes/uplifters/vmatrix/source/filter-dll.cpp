/**
\file       vmatrix.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dnodes::uplifters::vmatrix
{
void
Filter::load_int (::libs::icore::impl::base::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
  load_images (&finfo_);
}


void
Filter::transform_int (::libs::icore::impl::base::obj::dll::TransformInfo& info)
{
  prepare_transform (info);
  ::libs::utility::checks::throw_exception ("failed");
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  if (finfo_.req_update_files_)
  {
    load_images (&finfo_);
    finfo_.req_update_files_ = false;
  }

  // add offset for active data and corrected active data correct frame
  itransform ();
#endif
}


void
Filter::call_int (::libs::icore::impl::base::obj::dll::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (::libs::icore::impl::base::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (::libs::icore::impl::base::obj::PointState::enabled, ::libs::icore::impl::base::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (::libs::icore::impl::base::obj::PointState::enabled);
}
}   // namespace dnodes::uplifters::vmatrix
