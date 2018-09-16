#pragma once
/**
\file       app-paths.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties { namespace appl_paths {
/**
\brief  Реализация функционала "пути приложения". Полное описание функций в суперклассе.
*/
class AppPaths : public IAppPaths
{
  public:
  /// Конструктор.
  AppPaths ();

  virtual ~AppPaths ();

  AppPaths (const AppPaths& _obj) = delete;
  AppPaths& operator= (const AppPaths& _obj) = delete;

  //  IAppPaths implementation
  virtual std::string get_path (const appl_paths::TypePath& type) const override;
  virtual std::string get_suffix (const appl_paths::TypePath& type) const override;
  virtual void        load (const std::string& _company, const std::string& _app, const std::string& _ver) override;


  private:
  //  int types
  using path2string_type = std::map<TypePath, std::string>;      //< Тип для хранения соотвествия типа и строки.

  mutable path2string_type paths_;      //< Поле для быстрого преобразования типа пути в строку.
};

}}}      // namespace libs::iproperties::appl_paths
