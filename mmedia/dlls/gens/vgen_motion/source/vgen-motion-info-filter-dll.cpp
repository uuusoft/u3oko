/**
\file       vgen-motion-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_vgd_motion
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-motion-includes_int.hpp"
#include "vgen-motion-info-filter-dll.hpp"
#include "vgen-motion-filter-dll.hpp"

namespace dlls::gens::vgen_motion
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< props_type > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
}
}   // namespace dlls::gens::vgen_motion
