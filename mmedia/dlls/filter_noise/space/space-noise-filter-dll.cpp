/**
\file       space-noise-filter-dll.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
\brief      Файл реализации фильтрации в пространственной области
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "space-noise-includes_int.hpp"
#include "space-noise-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::filter_noise::space
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
  // std::this_thread::sleep_for (std::chrono::milliseconds (30000));   // debug
  init_pts (&info->pts_);
  finfo_.load (node);
  update_impl ();
  impl_->load_int ();
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


void
Filter::update_impl ()
{
  const auto& name = finfo_.rprops_->name_impl_;
  if ("rang" == name || "default" == name)
  {
    impl_.reset (new impl::rang::RangFilter);
    return;
  }

  U3_LOG_DATA_WRN ("unknown type filter impl" + TOLOG (name));
  impl_.reset (new impl::rang::RangFilter);
}
}   // namespace dlls::filter_noise::space
