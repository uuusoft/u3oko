#pragma once
/**
\file       iapplication.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
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
  void appl_init (const InitApplication&);

  /// Функция рабочего цикла модуля
  /// Вызывается в отдельном потоке
  void appl_work ();

  /// Функция удаления объекта модуля
  /// По завершению вызова модуль считается готовым к удалению из памяти
  /// true, если функция полностью удалила модуль, иначе требуется повторной вызов
  bool appl_deinit ();

  /// Функция принудительного завершение работы модуля в исключительных ситуациях, например по сигналу Ctlr+C
  void appl_force_stop ();

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
  bool init_ = false;   //< Флаг инициализации объекта
};
}   // namespace libs::link::appl
