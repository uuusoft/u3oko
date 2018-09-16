#pragma once
/**
\file       info-filter-dll.hpp
\brief      Включаемый файл для морфологических операций.
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2017
\copyright  www.uuusoft.com
\project    uuu_vgen_mops
\brief    
*/

namespace dlls { namespace gens { namespace vgen_mops {
/**
\brief  Загружаемые данные для фильтра морфологических операций над изображением.
*/
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = VideoMorphologyProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr props_;       //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;      //< Настроенный указатель на свойства (для удобства).
};

}}}      // namespace dlls::gens::vgen_mops
