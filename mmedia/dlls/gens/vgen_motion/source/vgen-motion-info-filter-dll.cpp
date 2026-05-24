/**
\file       vgen-motion-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< props_type > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::gens::vgen_motion
