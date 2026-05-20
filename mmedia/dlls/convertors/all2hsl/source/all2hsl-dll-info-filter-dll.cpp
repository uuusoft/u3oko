/**
\file       all2hsl-dll-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_all2hsl
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

namespace dlls::convertors::all2hsl
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  init ();
}

InfoFilter::~InfoFilter ()
{
}

void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoConvertProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::convertors::all2hsl
