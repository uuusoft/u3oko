/**
\file       vgen-conv3_11-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_vgen_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-conv3_11-includes_int.hpp"
#include "vgen-conv3_11-info-filter-dll.hpp"
#include "vgen-conv3_11-filter-dll.hpp"

namespace dlls::gens::vgen_conv3_11
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoConvolutionProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}


InfoFilter::~InfoFilter ()
{
}


bool
InfoFilter::load_int (const ::pugi::xml_named_node_iterator& node)
{
  super::load_int (node);
  return true;
}
}   // namespace dlls::gens::vgen_conv3_11
