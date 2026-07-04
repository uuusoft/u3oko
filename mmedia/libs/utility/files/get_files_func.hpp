#pragma once
/**
\file       get_files_func.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_lib_helpers
*/

namespace libs::utility::files
{
using get_files_func_type = std::function< bool (const boost::filesystem::path&) >;   //< Тип для проверки при построении списка файлов в вызове get_files

/// Функтор проверки узлов файловой системы для внесения их в выходной список
struct DefaultFileMask {
  DefaultFileMask (const std::string& val) :
    template_ (val)
  {
  }

  bool
  operator() (const boost::filesystem::path& obj) const
  {
    if (template_.empty ())
    {
      return true;
    }

    std::string ext = std::string ("?") + obj.extension ().string () + std::string ("?");
    return std::string::npos != template_.find (ext) ? true : false;
  }

  std::string template_;   //< Шаблон узлов
};


enum class IncludeSubFolders : std::uint32_t
{
  enabled  = 0x00,   //<
  disabled = 0x01,   //<
  unknown  = 0xFF    //< Не определенно для общности
};


enum class IncludeFiles : std::uint32_t
{
  enabled  = 0x00,   //<
  disabled = 0x01,   //<
  unknown  = 0xFF    //< Не определенно для общности
};


enum class Recursives : std::uint32_t
{
  enabled  = 0x00,   //<
  disabled = 0x01,   //<
  unknown  = 0xFF    //< Не определенно для общности
};


enum class Sorting : std::uint32_t
{
  disabled        = 0x00,   //<
  creation_time   = 0x01,   //<
  last_write_time = 0x02,   //<
  size            = 0x03,   //<
  name            = 0x04,   //<
  unknown         = 0xFF    //< Не определенно для общности
};


struct FileEnumParams {
  // EAI-CPP20
  // U3_ADD_DELETE_MOVE_COPY (FileEnumParams)

  IncludeSubFolders include_fiolders_ = IncludeSubFolders::disabled;
  IncludeFiles      include_files_    = IncludeFiles::enabled;
  Recursives        recursive_        = Recursives::disabled;
  Sorting           sorting_          = Sorting::disabled;
};


struct FileNode {
  std::string   name_;
  std::time_t   create_time_     = 0;
  std::time_t   last_write_time_ = 0;
  std::uint64_t size_            = 0;
};

/// Структура для хранения директории перечисления
struct NodeEnumFiles {
  NodeEnumFiles ()
  {
    files_.reserve (1 * 128);
  }

  void
  clear ()
  {
    name_.clear ();
    folders_.clear ();
    files_.clear ();
  }

  std::string                  name_;      //< Имя данной директории
  std::vector< NodeEnumFiles > folders_;   //< Дочерние директории данной
  std::vector< FileNode >      files_;     //< Файлы данной директории
};
/// Функция создает список из всех файлов c заданными расширениями в данной директории
/// \param[in]  root                     корневая директория
/// \param[out] enums                    структура данной директории, заданная параматрами
/// \param[in]  include_subdir           флаг, включить поддиректрии в перечисление
/// \param[in]  include_files            флаг, включить файлы в перечисление
/// \param[in]  include_recursive_items  флаг, включит рекурсивный режим перечисления
/// \param[in]  checker                  параметр фильтрации перечисления
void get_files (
  const std::string&         path,
  NodeEnumFiles&             enums,
  const FileEnumParams&      params,
  const get_files_func_type& checker);
}   // namespace libs::utility::files
