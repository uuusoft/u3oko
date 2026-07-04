/**
\file       gen-vgen-filter-dll-ifilter.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "gen-vgen-includes_int.hpp"
#include "memory"
#include "mmedia/libs/utility/thread/generic-thread-func.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::sources::gen_vgen
{
void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);

  finfo_.load (node);

  auto pdemons = ::libs::iproperties::helpers::cast_prop_demons ();
  auto ibuf    = pdemons->get_bufs_lockfree ()->impl ();
  auto ioptim  = pdemons->get_optim_lockfree ()->impl ();

  flip_y_     = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
  finfo_.buf_ = ibuf->create (0);
  finfo_.capture_fps_.set_fps (U3_CAST_FLOAT (finfo_.capture_props_->capi_.fps_));

  idata_source_impl_.init ();

  finfo_.recv_thread_ = std::make_unique< std::thread > (
    ::libs::utility::thread::generic_thread_funct< Filter >,
    libs::properties::vers::links::mids::mdata2appl,
    this,
    0u);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


auto
Filter::query_int (const ::libs::utility::utils::cuuid& par) -> ::libs::core::graph::IInterfGraphObj::raw_ptr
{
  const auto interf = ::libs::utility::uids::minor::get (par);
  if (interf == ::libs::utility::uids::minor::id_val::idata_source)
  {
    return &idata_source_impl_;
  }
  if (interf == ::libs::utility::uids::minor::id_val::ctrl_driver_dshow)
  {
    return &support_interf_;
  }
  return nullptr;
}


void
Filter::run_int ()
{
  if (auto driver = finfo_.proxy2hardware_.get_source_impl ())
  {
    driver->start ();
  }
}


void
Filter::stop_int ()
{
  finfo_.capture_impl_ = finfo_.null_impl_;
  if (auto driver = finfo_.proxy2hardware_.get_source_impl ())
  {
    driver->stop ();
  }
}
}   // namespace dlls::sources::gen_vgen
