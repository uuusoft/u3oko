//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       event-props-for-application.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilinks
\brief      Объявление структуры для группировки стандартных свойств-событий для приложения.
*/

namespace libs { namespace ilink { namespace appl {
/**
  \brief  Структура для группировки стандартных свойств приложения. 
          Хранит именно указатели, чтобы использовать непосредственно их во время работы с другими модулями, через стандартный интерфейс.
  */
struct EventPropsForApplication
{
  EventPropsForApplication ()
  {}

  ~EventPropsForApplication ()
  {}

  void
  init ()
  {
    //  debug
    ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::props::application::ApplicationProp> (main_appl_);
    ::libs::iproperties::helpers::get_and_cast_event<InfoCPUEvent> (info_cpu_);
    ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::props::modules::log::PropertyLogModuleEvent> (module_log_);
    ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::props::modules::storage::PropertyStorageModuleEvent> (storage_module_);
    return;
  }

  IEvent::ptr main_appl_;           //< Обшие свойства системы.
  IEvent::ptr info_cpu_;            //< Свойства аппартаного обеспечения.
  IEvent::ptr module_log_;          //< Свойства модуля логирования.
  IEvent::ptr storage_module_;      //< Свойства подсистемы хранения данных.

  //ApplicationProp::ptr            main_appl_;           //< Обшие свойства системы.
  //InfoCPUEvent::ptr               info_cpu_;            //< Свойства аппартаного обеспечения.
  //PropertyLogModuleEvent::ptr     module_log_;          //< Свойства модуля логирования.
  //PropertyStorageModuleEvent::ptr storage_module_;      //< Свойства подсистемы хранения данных.
};

}}}      // namespace libs::ilink::appl
