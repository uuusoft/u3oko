#pragma once
/**
\file       app-paths.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::appl_paths
{
/// Реализация функционала "пути приложения"
/// Полное описание функций в суперклассе
class AppPaths : public IAppPaths
{
  public:
  AppPaths ()          = default;
  virtual ~AppPaths () = default;

  AppPaths (const AppPaths& obj)            = delete;
  AppPaths& operator= (const AppPaths& obj) = delete;

  //  IAppPaths implementation
  virtual std::string get_path (const Paths& type) const override;
  virtual std::string get_path_suffix (const Paths& type) const override;
  virtual void        load_paths (const ::libs::link::appl::InitApplication& appl_info) override;

  private:
  //  internal typess
  using path2string_type = std::unordered_map< Paths, std::string >;

  mutable path2string_type paths_;   //< Поле для быстрого преобразования типа пути в строку
};
}   // namespace libs::iproperties::appl_paths
