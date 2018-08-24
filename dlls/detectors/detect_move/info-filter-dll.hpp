#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_detect_move
\brief      empty brief
*/

namespace dlls { namespace detectors { namespace detect_move {
/**
  \brief  Свойства фильтра по детектированию движения.
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = VideoDetectProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  ::libs::events::IEvent::ptr props_;       //< Загружаемые из xml файла свойства детекции фильтра.
  props_type::raw_ptr         rprops_;      //< Настроенный указатель на свойства (для удобства).


  private:
  void init ();
};

}}}      // namespace dlls::detectors::detect_move
