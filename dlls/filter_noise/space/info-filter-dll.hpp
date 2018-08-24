#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Файл интерфейса типа для расширения постоянных свойств фильтра фильтрации в пространственной области.
*/

namespace dlls { namespace filter_noise { namespace space {
/**
  \brief  Структура для расширения постоянных свойств узла графа обработки данных для фильтрации изображения в пространственной области.
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = VideoSpaceNoiseRemoverProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  ::libs::events::IEvent::ptr props_;                 //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;                //< Настроенный указатель на свойства (для удобства).
  ExpandedTimeStatistic       expand_time_algs_;      //< Поле для логирования времени работы.
  signed long long            counter_frame_;         //< Количество обработанных кадров.
};

}}}      // namespace dlls::filter_noise::space
