#pragma once
/**
\file       event-props-for-application.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilinks
\brief      Объявление структуры для группировки стандартных свойств-событий для приложения
*/

namespace libs::ilink::appl
{
enum class ApplEventProps : std::uint32_t
{
  main_appl      = 0x00,   //<
  info_cpu       = 0x01,   //<
  log_module     = 0x02,   //<
  storage_module = 0x03,   //<
  unknown        = 0xFF    //<
};

/// Структура для группировки стандартных свойств любого приложения
/// Хранит именно указатели, чтобы использовать непосредственно их во время работы с другими модулями, через стандартный интерфейс
struct EventPropsForApplication final {
  U3_HELPER_DISABLE_ACOPY_TYPE (EventPropsForApplication)

  EventPropsForApplication () = default;
  ~EventPropsForApplication ();

  void init ();

  syn::IEvent::ptr main_appl_properties_;   //< Обшие свойства системы
  syn::IEvent::ptr info_cpu_;               //< Свойства аппартаного обеспечения
  syn::IEvent::ptr module_log_;             //< Свойства модуля логирования
  syn::IEvent::ptr storage_module_;         //< Свойства подсистемы хранения данных
};
}   // namespace libs::ilink::appl
