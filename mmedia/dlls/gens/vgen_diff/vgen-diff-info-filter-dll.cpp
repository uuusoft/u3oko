/**
\file       vgen-diff-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff
*/
#include "vgen-diff-includes_int.hpp"
#include "vgen-diff-info-filter-dll.hpp"
#include "vgen-diff-filter-dll.hpp"

namespace dlls::gens::vgen_diff
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< ::libs::events_base::props::videos::gens::diff::VideoDiffProp > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
}
}   // namespace dlls::gens::vgen_diff
