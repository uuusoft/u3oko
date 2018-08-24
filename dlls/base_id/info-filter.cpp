//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
\brief      empty brief.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter.hpp"

namespace dlls { namespace base_id {

InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  XULOG_TRACE ("InfoFilter::InfoFilter: beg 0x" << this);
  rprops_ = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
  XULOG_TRACE (props_->get_mid ());
  XULOG_TRACE ("InfoFilter::InfoFilter: end 0x" << this);
}

}}      // namespace dlls::base_id
