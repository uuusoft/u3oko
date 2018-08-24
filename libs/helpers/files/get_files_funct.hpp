//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_files_funct.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_lib_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace files {

using get_files_funct_type = std::function<bool(const boost::filesystem::path&)>;      //< Тип для проверки при построении списка файлов в вызове get_files;
/**
  \brief  Функтор проверки узлов файловой системы для внесения их в выходной список.
  */
struct DefaultFileMask
{
  DefaultFileMask (const std::string& _template) :
    template_ (_template)
  {}

  bool
  operator() (const boost::filesystem::path& _obj) const
  {
    if (template_.empty ())
      {
        return true;
      }

    std::string _ext = std::string ("?") + _obj.extension ().string () + std::string ("?");
    return std::string::npos != template_.find (_ext) ? true : false;
  }

  std::string template_;      //< Шаблон узлов.
};
/**
  \brief  
  */
enum struct TypeIncludeSubFolders
{
  enabled,      //< ???
  disabled      //< ???
};
/**
  \brief  
  */
enum struct TypeIncludeFiles
{
  enabled,      //< ???
  disabled      //< ???
};
/**
  \brief  
  */
enum struct TypeRecursive
{
  enabled,      //< ???
  disabled      //< ???
};
/**
  \brief  Структура для хранения директории перечисления.
  */
struct NodeEnumFiles
{
  NodeEnumFiles ()
  {
    files_.reserve (256);
  }

  void
  clear ()
  {
    name_.clear ();
    folders_.clear ();
    files_.clear ();
    return;
  }

  std::string              name_;         //< Имя данной директории.
  std::list<NodeEnumFiles> folders_;      //< Дочерние директории данной.
  std::vector<std::string> files_;        //< Файлы данной директории.
};
/**
  \brief      Функция создает список из всех файлов c заданными расширениями в данной директории, 
  \param[in]  _root                     корневая директория.
  \param[out] _enums                    структура данной директории, заданная параматрами.            
  \param[in]  _include_subdir           флаг, включить поддиректрии в перечисление.
  \param[in]  _include_files            флаг, включить файлы в перечисление.
  \param[in]  _include_recursive_items  флаг, включит рекурсивный режим перечисления.
  \param[in]  _checker                  параметр фильтрации перечисления.
  */
void get_files (
  const std::string&           _path,
  NodeEnumFiles&               _enums,
  const TypeIncludeSubFolders& _include_subdirs,
  const TypeIncludeFiles&      _include_files,
  const TypeRecursive&         _include_recursive_items,
  get_files_funct_type         _checker = DefaultFileMask (""));

}}}      // namespace libs::helpers::files
