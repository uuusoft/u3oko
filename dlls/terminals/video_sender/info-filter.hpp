#pragma once
/**
\file       info-filter.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender {
/**
\brief  empty brief
*/
struct InfoFilter : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = EndPointProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  ::libs::events::IEvent::ptr props_;             //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;            //< Настроенный указатель на свойства (для удобства).
  long long                   count_frames_;      //< Счетчик обработанных кадров.
  IBaseId::weak_ptr           active_impl_;       //< Интерфейс для маршрутизации данных.
};

}}}      // namespace dlls::terminals::video_sender
