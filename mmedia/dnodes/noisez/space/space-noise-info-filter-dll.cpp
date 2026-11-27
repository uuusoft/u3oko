/**
\file       space-noise-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
*/
#include "space-noise-includes_int.hpp"
#include "space-noise-info-filter-dll.hpp"

namespace dnodes::noisez::space
{
InfoFilter::InfoFilter () :
  rprops_ (::libs::iproperties::helpers::create_event_in_list< syn::VideoSpaceNoiseRemoverProp > (ef_props_))
{
  // str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
  str2props_[ef_props_.front ()->get_mid ()] = rprops_;
}
}   // namespace dnodes::noisez::space
