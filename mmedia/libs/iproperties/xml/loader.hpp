#pragma once
/**
\file       loader.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.10.2016
\project    u3_iproperties_lib
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

  appl_paths::IAppPaths::cptr paths_;                                //< Указатель на хранилище путей к различным ресурсам
  bool                        disable_change_search_rule_ = false;   //< Флаг отключает изменение стандартного поведения при поиске файлов/каталогов (будут найдены все файлы/каталоги рекурсивным способом)
};

/// Тип для загрузки унифицированной загрузки константных ресурсов (скриптов, файлов и прочего)
/// Обеспечивает унифицированную работу с ними, вне зависимости от ОС
class Loader
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Loader)

  explicit Loader (const InitLoaderInfo& info);

  bool is_file_exist (const std::string& file_name, const appl_paths::Paths& storage_type) const;
  bool is_folder_exist (const std::string& file_name, const appl_paths::Paths& storage_type) const;

  void load (
    const std::string&                    file_name,
    const appl_paths::Paths&              storage_type,
    ::libs::helpers::mem::IBlockMem::ptr& bmem);

  void get_enum (
    const appl_paths::Paths&               storage_type,
    ::libs::helpers::files::NodeEnumFiles& fenum,
    const std::string&                     mask);

  private:
  InitLoaderInfo   iinfo_;   //< Информация инициализации объекта
  ILoaderImpl::ptr impl_;    //< Выбранная реализация для работы на данным момент в данной ОС
};
}   // namespace libs::iproperties::xml
