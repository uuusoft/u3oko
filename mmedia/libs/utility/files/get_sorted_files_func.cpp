/**
\file       get_sorted_files_func.cpp
\date       05.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_lib_helpers
*/
#include "../utility-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "get_sorted_files_func.hpp"

namespace libs::utility::files
{
auto
get_sort_by_time_folders (const std::string& path2sessions) -> std::vector< std::string >
{
  U3_ASSERT (!path2sessions.empty ());

  ::libs::utility::files::NodeEnumFiles enum_files;

  ::libs::utility::files::get_files (
    path2sessions,
    enum_files,
    { .include_fiolders_ = ::libs::utility::files::IncludeSubFolders::enabled, .include_files_ = ::libs::utility::files::IncludeFiles::disabled, .recursive_ = ::libs::utility::files::Recursives::disabled },
    ::libs::utility::files::DefaultFileMask (""));

  std::multimap< std::size_t, std::string > sort_files;
  std::vector< std::string >                folders;

  folders.reserve (enum_files.folders_.size ());

  for (const auto& file : enum_files.folders_)
  {
    ::boost::filesystem::path   path (::libs::utility::files::make_path (path2sessions, file.name_));
    ::boost::system::error_code error;
    const std::size_t           time = ::boost::filesystem::creation_time (path, error);
    // const std::size_t           time = ::boost::filesystem::last_write_time (path, error);

    U3_ASSERT_NT (!error, error.to_string ());
    U3_ASSERT_NT (time, VTOLOG (time));

    sort_files.insert ({ time, file.name_ });
  }

  std::ranges::for_each (
    sort_files,

    [&folders] (const decltype (sort_files)::value_type& node) -> void {
      folders.emplace_back (node.second);
      return;
    });

  return folders;
}


auto
get_sort_by_time_files (const std::string& path2session) -> std::vector< std::string >
{
  U3_ASSERT (!path2session.empty ());

  ::libs::utility::files::NodeEnumFiles enum_files;
  std::vector< std::string >            ret;

  ::libs::utility::files::get_files (
    path2session,
    enum_files,
    { .include_fiolders_ = ::libs::utility::files::IncludeSubFolders::disabled, .include_files_ = ::libs::utility::files::IncludeFiles::enabled, .recursive_ = ::libs::utility::files::Recursives::disabled },
    ::libs::utility::files::DefaultFileMask (""));

  boost::unordered_flat_map< std::size_t, std::string > sort_files;

  for (const auto& file : enum_files.files_)
  {
    ::boost::filesystem::path   path (::libs::utility::files::make_path (path2session, file.name_));
    ::boost::system::error_code error;
    const std::size_t           time = ::boost::filesystem::last_write_time (path, error);

    U3_ASSERT (!error);
    U3_ASSERT (sort_files.end () == sort_files.find (time));
    U3_ASSERT (time);

    sort_files[time] = file.name_;
  }

  std::ranges::for_each (
    sort_files,

    [&ret] (const decltype (sort_files)::value_type& node) -> void {
      ret.push_back (node.second);
      return;
    });
  return ret;
}
}   // namespace libs::utility::files
