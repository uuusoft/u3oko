/**
\file       time-noise-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-includes_int.hpp"
#include "time-noise-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::filter_noise::time
{
Filter::Filter ()
{
}


Filter::~Filter ()
{
}


void
Filter::load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);

  finfo_.load (node);

  update_impl ();
  finfo_.impl_->load_int ();
}


void
Filter::transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
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


void
Filter::run_int ()
{
  if (finfo_.impl_)
  {
    // impl_->run ();
  }
}


void
Filter::stop_int ()
{
  if (finfo_.impl_)
  {
    // impl_->stop ();
  }
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
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
  if ("median1" == name)
  {
    finfo_.impl_.reset (new impl::med1::Med1Impl);
    return;
  }
  if ("median2" == name)
  {
    finfo_.impl_.reset (new impl::med2::Med2Impl);
    return;
  }
  if ("median3" == name)
  {
    finfo_.impl_.reset (new impl::med3::Med3Impl);
    return;
  }

  U3_LOG_DATA_WRN ("unknown impl time filter" + TOLOG (name));
  finfo_.impl_.reset (new impl::med1::Med1Impl);
}
}   // namespace dlls::filter_noise::time
