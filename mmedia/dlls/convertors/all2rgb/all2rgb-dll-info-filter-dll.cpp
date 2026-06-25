/**
\file       all2rgb-dll-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_all2rgb
*/
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"

namespace dlls::convertors::all2rgb
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoConvertProp > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
}
}   // namespace dlls::convertors::all2rgb
