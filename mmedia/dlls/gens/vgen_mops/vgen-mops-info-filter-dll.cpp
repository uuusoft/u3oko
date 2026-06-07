/**
\file       vgen-mops-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2017
\project    u3_vgen_mops
\brief      Реализация загружаемых свойств фильтра МО
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-includes_int.hpp"
#include "vgen-mops-info-filter-dll.hpp"
#include "vgen-mops-filter-dll.hpp"

namespace dlls::gens::vgen_mops
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoMorphologyProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::gens::vgen_mops
