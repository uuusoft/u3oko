/**
\file       space-noise-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_filter_space
*/
#include "space-noise-includes_int.hpp"
#include "space-noise-info-filter-dll.hpp"

namespace dlls::noisez::space
{
InfoFilter::InfoFilter ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoSpaceNoiseRemoverProp > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });

  // auto temp = ::libs::iproperties::helpers::create_event< syn::MedianSpaceFilterProp > (rprops_->impl_info_);
  // str2props_.insert (str2prop_type::value_type (rprops_->impl_info_->get_mid (), temp));
}
}   // namespace dlls::noisez::space
