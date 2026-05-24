/**
\file       space-noise-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_filter_space
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "space-noise-includes_int.hpp"
#include "space-noise-info-filter-dll.hpp"

namespace dlls::filter_noise::space
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  counter_frame_ (0)
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoSpaceNoiseRemoverProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));

  auto temp = ::libs::iproperties::helpers::create_event< syn::MedianSpaceFilterProp > (rprops_->impl_info_);
  str2props_.insert (str2prop_type::value_type (rprops_->impl_info_->get_mid (), temp));
}


InfoFilter::~InfoFilter ()
{
}
}   // namespace dlls::filter_noise::space
