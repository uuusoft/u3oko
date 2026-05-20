/**
\file       vgen-diff-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    uuu_vgen_diff
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-diff-includes_int.hpp"
#include "vgen-diff-info-filter-dll.hpp"
#include "vgen-diff-filter-dll.hpp"

namespace dlls::gens::vgen_diff
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
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< ::libs::ievents::props::videos::gens::diff::VideoDiffProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::gens::vgen_diff
