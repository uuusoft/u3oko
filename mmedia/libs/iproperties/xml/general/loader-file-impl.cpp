/**
\file       loader-file-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "../libs-iproperties-xml-includes_int.hpp"
#include "mmedia/libs/proxy/proxy/iproperties-proxy.hpp"
#include "loader-file-impl.hpp"

namespace libs::iproperties::xml::general
{
auto
is_special_folder_for_libs (const appl_paths::Paths& path_type) -> bool
{
#if (U3_BUILD_MODULES_AS_LIBS == 1)
  return appl_paths::Paths::bins == path_type || appl_paths::Paths::emulate_bins == path_type;
#else
  return false;
#endif
}

LoaderFileImpl::LoaderFileImpl (InitLoaderInfo info) :
  iinfo_ (std::move (info))
{
}


void
LoaderFileImpl::get_enum_int (
  const LoaderFileImpl::lfi_path_type&   path_type,
  ::libs::utility::files::NodeEnumFiles& enum_files,
  const std::string&                     mask)
{
  U3_XLOG_DBG ("LoaderFileImpl::get_enum_int" + VTOLOG (is_special_folder_for_libs (path_type)) + TOLOG (to_string (path_type)));
  enum_files.clear ();

  if (is_special_folder_for_libs (path_type))
  {
    enum_files.files_ = ::libs::proxy::get_list_dlls_as_libs ();
    return;
  }

  const std::string root = iinfo_.paths_->get_path (path_type);
  U3_CHECK (::libs::utility::files::is_folder (root), "root not dir" + root);

  constexpr auto sub_folders = ::libs::utility::files::IncludeSubFolders::enabled;
  constexpr auto files       = ::libs::utility::files::IncludeFiles::enabled;
  constexpr auto recur       = ::libs::utility::files::Recursives::enabled;

  ::libs::utility::files::get_files (
    root,
    enum_files,
    { .include_fiolders_ = sub_folders, .include_files_ = files, .recursive_ = recur },
    ::libs::utility::files::DefaultFileMask (mask));
}


auto
LoaderFileImpl::is_exist_file_int (
  const std::string&                   file_name,
  const LoaderFileImpl::lfi_path_type& path_type) const -> bool
{
  U3_XLOG_DEV ("LoaderFileImpl::is_exist_file_int" + VTOLOG (is_special_folder_for_libs (path_type)) + TOLOG (to_string (path_type)));
  if (is_special_folder_for_libs (path_type))
  {
    auto files = ::libs::proxy::get_list_dlls_as_libs ();
    for (const auto& file : files)
    {
      if (file.name_ == file_name)
      {
        U3_XLOG_DBG ("LoaderFileImpl::is_exist_file_int file found" + TOLOG (file_name));
        return true;
      }
    }
    return false;
  }

  const auto dir_path  = iinfo_.paths_->get_path (path_type);
  const auto file_path = ::libs::utility::files::make_path (dir_path, file_name);
  return ::libs::utility::files::is_file_exist (file_path);
}


auto
LoaderFileImpl::is_exist_folder_int (
  const std::string&                   file_name,
  const LoaderFileImpl::lfi_path_type& path_type) const -> bool
{
  return is_exist_file_int (file_name, path_type);
}


auto
LoaderFileImpl::get_int (
  const std::string&                    file_name,
  const LoaderFileImpl::lfi_path_type&  path_type,
  ::libs::utility::mem::IBlockMem::ptr& ret) -> bool
{
  const auto dir_path  = iinfo_.paths_->get_path (path_type);
  const auto file_path = ::libs::utility::files::make_path (dir_path, file_name);
  return ::libs::utility::files::load_file2mem (file_path, ret);
}
}   // namespace libs::iproperties::xml::general
