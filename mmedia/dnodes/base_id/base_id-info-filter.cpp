/**
\file       base_id-info-filter.cpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
*/
#include "base_id-includes_int.hpp"
#include "base_id-info-filter.hpp"

namespace dnodes::base_id
{
InfoFilter::InfoFilter () :
  rprops_ (::libs::iproperties::helpers::create_event_in_list< syn::BaseIdProp > (ef_props_))
{
  // str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
  str2props_[ef_props_.front ()->get_mid ()] = rprops_;
}
}   // namespace dnodes::base_id
