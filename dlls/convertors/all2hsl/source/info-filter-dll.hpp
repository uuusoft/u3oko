//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_all2hsl
\brief      empty brief
*/

namespace dlls { namespace convertors { namespace all2hsl {
/**
  \brief
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  public:
  // ext types
  using props_type = VideoConvertProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr props_;            //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;           //< Настроенный указатель на свойства (для удобства).
  bool                        strip_color_;      //< Флаг-требование, отбрасывать цвет при преобразовании.
};

}}}      // namespace dlls::convertors::all2hsl
