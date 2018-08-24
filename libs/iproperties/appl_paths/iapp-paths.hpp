#pragma once
/**
\file       iapp-paths.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      Объявление интерфейса "файловые пути приложения".
*/

namespace libs { namespace iproperties { namespace appl_paths {
/**
  \brief  Интерфейс "файловые пути приложения".
          Обеспечивает (вне зависимости от ОС), генерацию путей и их валидацию.
  */
class IAppPaths
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IAppPaths);

  virtual ~IAppPaths ()
  {}
  /**
    \brief      Функция полного конструирования объекта.
    \param[in]  _company  компания.
    \param[in]  _appl     приложение.
    \param[in]  _ver      версия приложения (опционально).
    */
  virtual void load (
    const std::string& _company,
    const std::string& _appl,
    const std::string& _ver) = 0;
  /**
    \brief      Функция получения конечного подкаталога по типу пути.
    \param[in]  _type тип пути.
    \return     строка полного пути.
    */
  virtual std::string get_path (const appl_paths::TypePath& _type) const = 0;
  /**
    \brief      Функция получения конечного подкаталога по типу пути.
    \param[in]  _type тип пути.
    \return     строка конечного подкаталога.
    */
  virtual std::string get_suffix (const appl_paths::TypePath& _type) const = 0;


  protected:
  IAppPaths ()
  {}
};

}}}      // namespace libs::iproperties::appl_paths
