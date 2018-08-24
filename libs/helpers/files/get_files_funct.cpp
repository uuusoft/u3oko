//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get_files_funct.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_lib_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "includes.hpp"
#include "get_files_funct.hpp"

namespace libs { namespace helpers { namespace files {

void
get_files_int (
  const std::string&           _root_path,
  const std::string&           _add_path,
  NodeEnumFiles&               _enums,
  const TypeIncludeSubFolders& _inlcude_subdirs,
  const TypeIncludeFiles&      _include_files,
  const TypeRecursive&         _include_recursive_items,
  get_files_funct_type         _checker)
{
  const std::string         _path = ::libs::helpers::files::make_path (_root_path, _add_path);
  ::boost::filesystem::path _root = _path;

  if (!boost::filesystem::exists (_path))
    {
      return;
    }

  if (!boost::filesystem::is_directory (_path))
    {
      return;
    }

  boost::filesystem::directory_iterator _it_dir (_root);

  while (_it_dir != boost::filesystem::directory_iterator ())
    {
      const boost::filesystem::path& _full_path = _it_dir->path ();
      const std::string              _file_name = _full_path.filename ().string ();
      const std::string              _add_name  = ::libs::helpers::files::make_path (_add_path, _file_name);

      if (!_checker (_full_path))
        {
          ++_it_dir;
          continue;
        }

      if (is_directory (_full_path))
        {
          if (TypeIncludeSubFolders::disabled != _inlcude_subdirs)
            {
              _enums.folders_.push_back (NodeEnumFiles ());

              auto& _add_folder = _enums.folders_.back ();

              _add_folder.name_ = _file_name;

              if (TypeRecursive::enabled == _include_recursive_items)
                {
                  get_files_int (
                    _root_path,
                    _add_name,
                    _add_folder,
                    _inlcude_subdirs,
                    _include_files,
                    _include_recursive_items,
                    _checker);
                }
            }
        }
      else
        {
          if (TypeIncludeFiles::disabled != _include_files)
            {
              _enums.files_.push_back (_file_name);
            }
        }

      ++_it_dir;
    }

  return;
}


void
get_files (
  const std::string&           _path,
  NodeEnumFiles&               _enums,
  const TypeIncludeSubFolders& _inlcude_subdirs,
  const TypeIncludeFiles&      _include_files,
  const TypeRecursive&         _include_recursive_items,
  get_files_funct_type         _checker)
{
  get_files_int (
    _path,
    std::string (""),
    _enums,
    _inlcude_subdirs,
    _include_files,
    _include_recursive_items,
    _checker);

  return;
}

}}}      // namespace libs::helpers::files
