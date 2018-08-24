//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ishared-property.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "ishared-property.hpp"

namespace libs { namespace properties {

ISharedProperty::ISharedProperty ()
{}


ISharedProperty::~ISharedProperty ()
{}


bool
ISharedProperty::self_test () const
{
  guard_type _grd (mtx_);
  return self_test_int ();
}


void*
ISharedProperty::cast2top ()
{
  auto _ret = cast2top_int ();
  UASSERT (_ret);
  return _ret;
}


ISharedProperty::sync_type&
ISharedProperty::get_sync ()
{
  return mtx_;
}

}}      // namespace libs::properties
