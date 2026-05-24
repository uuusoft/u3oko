/**
\file       get_sorted_files_funct.cpp
\date       05.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_lib_helpers
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "get_sorted_files_func.hpp"

namespace libs::helpers::files
{
std::vector< std::string >
get_sort_by_time_folders (const std::string& path2sessions)
{
  U3_ASSERT (!path2sessions.empty ());

  ::libs::helpers::files::NodeEnumFiles enum_files;
  std::vector< std::string >            folders;

  ::libs::helpers::files::get_files (
    path2sessions,
    enum_files,
    { ::libs::helpers::files::IncludeSubFolders::enabled, ::libs::helpers::files::IncludeFiles::disabled, ::libs::helpers::files::Recursives::disabled },
    ::libs::helpers::files::DefaultFileMask (""));

  std::map< std::size_t, std::string > sort_files;

  for (const auto& file : enum_files.folders_)
  {
    ::boost::filesystem::path   path (::libs::helpers::files::make_path (path2sessions, file.name_));
    ::boost::system::error_code error;
    const std::size_t           time = ::boost::filesystem::last_write_time (path, error);

    U3_ASSERT_NT (!error, error.to_string ());
    U3_ASSERT_NT (time, VTOLOG (time));

    sort_files[time] = file.name_;
  }

  std::for_each (
    sort_files.begin (),
    sort_files.end (),
    [&folders] (const decltype (sort_files)::value_type& node) {
      folders.push_back (node.second);
      return;
    });

  return folders;
}


std::vector< std::string >
get_sort_by_time_files (const std::string& path2session)
{
  U3_ASSERT (!path2session.empty ());

  ::libs::helpers::files::NodeEnumFiles enum_files;
  std::vector< std::string >            ret;

  ::libs::helpers::files::get_files (
    path2session,
    enum_files,
    { ::libs::helpers::files::IncludeSubFolders::disabled, ::libs::helpers::files::IncludeFiles::enabled, ::libs::helpers::files::Recursives::disabled },
    ::libs::helpers::files::DefaultFileMask (""));

  std::unordered_map< std::size_t, std::string > sort_files;

  for (const auto& file : enum_files.files_)
  {
    ::boost::filesystem::path   path (::libs::helpers::files::make_path (path2session, file.name_));
    ::boost::system::error_code error;
    const std::size_t           time = ::boost::filesystem::last_write_time (path, error);

    U3_ASSERT (!error);
    U3_ASSERT (sort_files.end () == sort_files.find (time));
    U3_ASSERT (time);

    sort_files[time] = file.name_;
  }

  std::for_each (
    sort_files.begin (),
    sort_files.end (),
    [&ret] (const decltype (sort_files)::value_type& node) {
      ret.push_back (node.second);
      return;
    });
  return ret;
}
}   // namespace libs::helpers::files
