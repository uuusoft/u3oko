#pragma once
/**
\file       state-process-event-ext.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
\brief      Файл объявления типа хранения состония обработки события внутри основного модуля
*/

namespace libs::ilink::appl
{
/// Структура для расширения базового типа необходимим свойствами  для хранения состояния обработки события
class StateProcessEventExt final : public ::libs::link::StateProcessEvent
{
  public:
  StateProcessEventExt ();
  virtual ~StateProcessEventExt ();

  void reset ();

  ::libs::link::ILink::ptr source_;   //< Источник события Используется для завершения транзакции
  ::libs::link::ILink::ptr dest_;     //< Получатель события Используется для его обработки и формирования результат

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::link::StateProcessEvent)
};

/// Вспомогательная функция для преобразования структуры в строку
/// Для трассировки
std::string to_string (const StateProcessEventExt&);
}   // namespace libs::ilink::appl
