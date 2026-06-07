#pragma once
/**
\file       iapp-paths.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

// U3-REFACT
namespace libs::link::appl
{
struct InitApplication;
}

namespace libs::iproperties::appl_paths
{
/// Интерфейс "файловые пути приложения"
/// Обеспечивает (вне зависимости от ОС), генерацию путей и их валидацию
class IAppPaths
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IAppPaths)

  virtual ~IAppPaths () = default;

  /// Функция полного конструирования объекта
  /// \param[in]  appl_info
  virtual void load_paths (const ::libs::link::appl::InitApplication&) = 0;

  /// Функция получения конечного подкаталога по типу пути
  /// \param[in]  type тип пути
  /// \return     строка полного пути
  virtual std::string get_path (const appl_paths::Paths&) const = 0;

  /// Функция получения конечного подкаталога по типу пути
  /// \param[in]  type тип пути
  /// \return     строка конечного подкаталога
  virtual std::string get_path_suffix (const appl_paths::Paths&) const = 0;

  protected:
  IAppPaths () = default;
};
}   // namespace libs::iproperties::appl_paths
