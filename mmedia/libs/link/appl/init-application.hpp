#pragma once
/**
\file       init-application.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    uuu_link
\brief      Объявление структура для инициализации приложения
*/

namespace libs::link::appl
{
/// Структура для группировки данных по инициализации модуля приложения связи
struct InitApplication final {
  public:
  InitApplication ()  = default;
  ~InitApplication () = default;

  bool
  check () const
  {
    return company_name_.empty () || appl_name_.empty () || service_name_.empty () ? false : true;
  }

  std::string service_name_ = consts::text::default_service_name;   //< Имя сервиса, опциональное
  std::string company_name_ = consts::text::default_company_name;   //< Имя компании-разработчика модуля
  std::string appl_name_    = consts::text::default_appl_name;      //< Имя приложения
  std::string subsys_name_  = {};                                   //< Имя подсистемы, приложения
  std::string lib_name_     = {};                                   //< Имя файла с разделяемым кодом, который содержит в себе модуль приложения
};
}   // namespace libs::link::appl
