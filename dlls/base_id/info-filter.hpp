#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
\brief      empty brief.
*/

namespace dlls { namespace base_id {
//  forward
class Filter;
/**
  \brief  empty brief
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  typedef ::libs::ievents::props::base_id::BaseIdProp props_type;

  InfoFilter ();

  virtual ~InfoFilter ()
  {}

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  ::libs::events::IEvent::ptr props_;       //< ???
  props_type::raw_ptr         rprops_;      //< Ќастроенный указатель на свойства (дл€ удобства).
};

}}      // namespace dlls::base_id
