//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace uplifters { namespace vcorrect {

InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  sync_ok_ (false)
{
  init ();
}


InfoFilter::~InfoFilter ()
{}


void
InfoFilter::init ()
{
  sync_ok_ = false;
  rprops_  = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
  return;
}

void
InfoFilter::sync_int (bool _force)
{
  if (sync_ok_ && !_force)
    {
      return;
    }

  XULOG_TRACE (::libs::events::helpers::to_str (rprops_));
  if (auto _impl = active_impl_.lock ())
    {
      _impl->update_property (rprops_);
    }
  sync_ok_ = true;
  return;
}


bool
InfoFilter::load_int (const base_functs::xml::itn& _node)
{
  sync_ok_ = false;
  return super::load_int (_node);
}

}}}      // namespace dlls::uplifters::vcorrect
