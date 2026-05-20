/**
\file       base_id-info-filter.cpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_base_id_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "base_id-includes_int.hpp"
#include "base_id-info-filter.hpp"

namespace dlls::base_id
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::BaseIdProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::base_id
