#pragma once
/**
\file       iapplication.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::link::appl
{
/// Интерфейс, который должен поддерживать любой модуль подсистемы (приложение, htpp, data storage, net, data process etc)
class IApplication
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IApplication)
  U3_ADD_DELETE_MOVE_COPY (IApplication)

  IApplication ()          = default;
  virtual ~IApplication () = default;

  /// Функция конструирования объекта модуля
  /// По завершению вызова модуль считается готовым к работе
  auto appl_init (const InitApplication&) -> void;

  /// Функция рабочего цикла модуля
  /// Вызывается в отдельном потоке
  auto appl_work () -> void;

  /// Функция удаления объекта модуля
  /// По завершению вызова модуль считается готовым к удалению из памяти
  /// true, если функция полностью удалила модуль, иначе требуется повторной вызов
  auto appl_deinit () -> bool;

  /// Функция принудительного завершение работы модуля в исключительных ситуациях, например по сигналу Ctlr+C
  auto appl_force_stop () -> void;

  protected:
  // IApplication interface
  virtual auto appl_init_int (const InitApplication&) -> void  = 0;
  virtual auto init_links_int (const InitApplication&) -> void = 0;
  virtual auto init_appl_folders_int () -> void                = 0;
  virtual auto init_proxys_int () -> void                      = 0;
  virtual auto init_appl_data_int () -> void                   = 0;
  virtual auto init_done_int () -> void                        = 0;
  virtual auto appl_work_int () -> void                        = 0;
  virtual auto update_catch_funcs_int () -> void               = 0;
  virtual auto appl_force_stop_int () -> void                  = 0;
  virtual auto appl_deinit_int () -> bool                      = 0;

  ::libs::link::appl::InitApplication appl_info_;   //<

  private:
  bool init_ { false };   //< Флаг инициализации объекта
};
}   // namespace libs::link::appl
