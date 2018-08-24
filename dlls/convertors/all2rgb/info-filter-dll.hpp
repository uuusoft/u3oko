#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_all2rgb
\brief      empty brief
*/

namespace dlls { namespace convertors { namespace all2rgb {
/**
  \brief
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = VideoConvertProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  void init ();

  ::libs::events::IEvent::ptr props_;       //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;      //< Настроенный указатель на свойства (для удобства).
};

}}}      // namespace dlls::convertors::all2rgb
