#pragma once
/**
\file       iapplication.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IApplication)

  IApplication ()          = default;
  virtual ~IApplication () = default;

  IApplication (const IApplication&)            = delete;
  IApplication& operator= (const IApplication&) = delete;

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
  virtual void appl_init_int (const InitApplication&)  = 0;
  virtual void init_links_int (const InitApplication&) = 0;
  virtual void init_appl_folders_int ()                = 0;
  virtual void init_proxys_int ()                      = 0;
  virtual void init_appl_data_int ()                   = 0;
  virtual void init_done_int ()                        = 0;
  virtual void appl_work_int ()                        = 0;
  virtual bool appl_deinit_int ()                      = 0;
  virtual void update_catch_funcs_int ()               = 0;
  virtual void appl_force_stop_int ()                  = 0;

  ::libs::link::appl::InitApplication appl_info_;   //<

  private:
  bool init_ = false;   //< Флаг инициализации объекта
};
}   // namespace libs::link::appl
