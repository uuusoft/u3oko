/**
\file       get_files_func.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_lib_helpers
*/
#include "../utility-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "get_files_func.hpp"

namespace libs::utility::files
{
void
get_files_int (
  const std::string&         root_path,
  const std::string&         add_path,
  NodeEnumFiles&             enums,
  const FileEnumParams&      params,
  const get_files_func_type& checker)
{
  const std::string         path = ::libs::utility::files::make_path (root_path, add_path);
  ::boost::filesystem::path root = path;

  if (!boost::filesystem::exists (path) || !boost::filesystem::is_directory (path))
  {
    U3_XLOG_WARN ("path not exist or not directory" + TOLOG (path) + VTOLOG (boost::filesystem::exists (path)) + VTOLOG (boost::filesystem::is_directory (path)));
    return;
  }

  boost::filesystem::directory_iterator it_dir (root);

  while (it_dir != boost::filesystem::directory_iterator ())
  {
    const auto& full_path = it_dir->path ();
    const auto  file_name = full_path.filename ().string ();
    const auto  add_name  = ::libs::utility::files::make_path (add_path, file_name);

    if (!checker (full_path))
    {
      ++it_dir;
      continue;
    }

    if (is_directory (full_path))
    {
      if (IncludeSubFolders::disabled != params.include_fiolders_)
      {
        enums.folders_.emplace_back ();
        auto& add_folder = enums.folders_.back ();
        add_folder.name_ = file_name;

        if (Recursives::enabled == params.recursive_)
        {
          get_files_int (
            root_path,
            add_name,
            add_folder,
            params,
            checker);
        }
      }
    }
    else
    {
      if (IncludeFiles::disabled != params.include_files_)
      {
#ifdef U3_OS_ANDROID
        U3_XLOG_DEV ("U3TODO: Not implemented at boost library - ::boost::filesystem::creation_time");
        enums.files_.push_back (
          { file_name,
            0,
            ::boost::filesystem::last_write_time (full_path),
            ::boost::filesystem::file_size (full_path) });
#else
        enums.files_.push_back (
          { file_name,
            ::boost::filesystem::creation_time (full_path),
            ::boost::filesystem::last_write_time (full_path),
            ::boost::filesystem::file_size (full_path) });
#endif
      }
    }

    ++it_dir;
  }

  if (Sorting::disabled != params.sorting_)
  {
    std::ranges::sort (
      enums.files_,

      [&params] (const FileNode& lhs, const FileNode& rhs) -> bool {
        switch (params.sorting_)
        {
        case Sorting::creation_time:
          return lhs.create_time_ < rhs.create_time_;
        case Sorting::last_write_time:
          return lhs.last_write_time_ < rhs.last_write_time_;
        case Sorting::size:
          return lhs.size_ < rhs.size_;
        case Sorting::name:
        default:
          return lhs.name_ < rhs.name_;
        }
      });
  }
}

void
get_files (
  const std::string&         path,
  NodeEnumFiles&             enums,
  const FileEnumParams&      params,
  const get_files_func_type& checker)
{
  get_files_int (path, std::string (""), enums, params, checker);
}
}   // namespace libs::utility::files
