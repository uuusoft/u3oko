/**
\file       space-noise-filter-dll.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
\brief      Файл реализации фильтрации в пространственной области
*/
#include "memory"
#include "space-noise-includes_int.hpp"
#include "space-noise-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::noisez::space
{
void
Filter::load_int (
  ::libs::icore::impl::var1::obj::FilterInfo* info,
  const ::pugi::xml_named_node_iterator&      node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
  update_impl ();
  impl_->load_int ();
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
Filter::update_impl ()
{
  const auto& name = finfo_.rprops_->name_impl_;
  if ("rang" == name || "default" == name)
  {
    impl_ = std::make_unique< impl::rang::RangFilter > ();
    return;
  }

  U3_LOG_DATA_WRN ("unknown type filter impl" + TOLOG (name));
  impl_ = std::make_unique< impl::rang::RangFilter > ();
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  itransform ();
}


void
Filter::itransform ()
{
  impl_->transform_int (id_obj_, *transinfo_, finfo_, pbuf_);
}
}   // namespace dlls::noisez::space
