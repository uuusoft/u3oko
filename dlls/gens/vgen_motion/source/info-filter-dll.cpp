//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_vgd_motion
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace gens { namespace vgen_motion {

InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  init ();
}


InfoFilter::~InfoFilter ()
{}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
  return;
}

}}}      // namespace dlls::gens::vgen_motion
