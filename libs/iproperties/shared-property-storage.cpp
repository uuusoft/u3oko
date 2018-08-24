//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       shared-property-storage.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "shared-property-storage.hpp"

namespace libs { namespace iproperties {

SharedPropertyStorage::SharedPropertyStorage ()
{}


SharedPropertyStorage::~SharedPropertyStorage ()
{
  guard_type _grd (mtx_);
  props_.clear ();
}


ISharedProperty::raw_ptr
SharedPropertyStorage::get (const key_property_type& _key)
{
  XULOG_TRACE ("uuu_helpers::SharedPropertyStorage::get, " << _key);
  UASSERT (!_key.empty ());

  guard_type _grd (mtx_);
  auto       _find = props_.find (_key);

  if (_find == props_.end ())
    {
      XULOG_ERROR ("uuu_helpers::SharedPropertyStorage::get failed, not found, " << _key);
      UASSERT_SIGNAL ("failed");
      return nullptr;
    }
  return _find->second.get ();
}


void
SharedPropertyStorage::set_prop (const key_property_type& _key, const ISharedProperty::ptr& _ptr)
{
  XULOG_TRACE ("uuu_helpers::SharedPropertyStorage::set_prop, " << _key);
  UASSERT (!_key.empty ());

  guard_type _grd (mtx_);

  {
    auto _it2old = props_.find (_key);
    if (props_.end () != _it2old)
      {
        //  перезапись допустима только для пустого значения.
        if (_it2old->second)
          {
            UASSERT_SIGNAL ("failed");
            return;
          }
      }
  }

  props_[_key] = _ptr;
  return;
}


void
SharedPropertyStorage::reset_prop (const key_property_type& _key)
{
  XULOG_TRACE ("uuu_helpers::SharedPropertyStorage::reset_prop, " << _key);
  UASSERT (!_key.empty ());

  guard_type _grd (mtx_);
  props_[_key] = ISharedProperty::ptr ();
  return;
}

}}      // namespace libs::iproperties
