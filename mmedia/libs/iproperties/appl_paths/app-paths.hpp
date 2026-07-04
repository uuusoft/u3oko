#pragma once
/**
\file       app-paths.hpp
\author     Erashov Anton erashov2026@proton.me
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

  //  IAppPaths overrides
  virtual auto get_path (const Paths&) const -> std::string override;
  virtual auto get_path_suffix (const Paths&) const -> std::string override;
  virtual auto load_paths (const ::libs::link::appl::InitApplication&) -> void override;

  private:
  //  internal typess
  using path2string_type = boost::unordered_flat_map< Paths, std::string >;

  mutable path2string_type paths_;   //< Поле для быстрого преобразования типа пути в строку
};
}   // namespace libs::iproperties::appl_paths
