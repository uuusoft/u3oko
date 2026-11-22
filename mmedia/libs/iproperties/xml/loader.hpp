#pragma once
/**
\file       loader.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.10.2016
*/

namespace libs::iproperties::xml
{
/// Тип для группировки данных для инициализации Loader
struct InitLoaderInfo final {
  explicit InitLoaderInfo (
    appl_paths::IAppPaths::cptr paths,
    bool                        disable_change_search_rule = false) :

    paths_ (paths),
    disable_change_search_rule_ (disable_change_search_rule)
  {
  }

  appl_paths::IAppPaths::cptr paths_;                                  //< Указатель на хранилище путей к различным ресурсам
  bool                        disable_change_search_rule_ { false };   //< Флаг отключает изменение стандартного поведения при поиске файлов/каталогов (будут найдены все файлы/каталоги рекурсивным способом)
};

/// Тип для загрузки унифицированной загрузки константных ресурсов (скриптов, файлов и прочего)
/// Обеспечивает унифицированную работу с ними, вне зависимости от ОС
class Loader
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (Loader)

  explicit Loader (InitLoaderInfo info);

  auto is_file_exist (const std::string&, const appl_paths::Paths&) const -> bool;
  auto is_folder_exist (const std::string&, const appl_paths::Paths&) const -> bool;
  auto load (const std::string&, const appl_paths::Paths&, syn::IBlockMem::ptr&) -> void;
  auto get_enum (const appl_paths::Paths&, syn::NodeEnumFiles&, const std::string&) -> void;

  private:
  InitLoaderInfo   iinfo_;   //< Информация инициализации объекта
  ILoaderImpl::ptr impl_;    //< Выбранная реализация для работы на данным момент в данной ОС
};
}   // namespace libs::iproperties::xml
