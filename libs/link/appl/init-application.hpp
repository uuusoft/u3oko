#pragma once
/**
\file       init-application.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      Объявление структура для инициализации приложения.
*/

namespace libs { namespace link { namespace appl {
/**
\brief  Структура для группировки данных по инициализации модуля приложения связи.
*/
struct InitApplication
{
  public:
  InitApplication ()
  {}

  ~InitApplication ()
  {}

  std::string name_lib_;          //< Имя файла с разделяемым кодом, который содержит в себе модуль приложения.
  std::string name_company_;      //< Имя компании-разработчика модуля.
  std::string name_appl_;         //< Имя приложения.
  std::string name_subsys_;       //< Имя подсистемы, приложения.
};

}}}      // namespace libs::link::appl
