/**
\file       loader-file-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/proxy/proxy/iproperties-proxy.hpp"
#include "../libs-iproperties-xml-includes_int.hpp"
#include "loader-file-impl.hpp"

namespace libs::iproperties::xml::general
{
bool
is_special_folder_for_libs (const appl_paths::Paths& path_type)
{
#if (U3_BUILD_MODULES_AS_LIBS == 1)
  return appl_paths::Paths::bins == path_type || appl_paths::Paths::emulate_bins == path_type;
#else
  return false;
#endif
}

LoaderFileImpl::LoaderFileImpl (const InitLoaderInfo& info) :
  iinfo_ (info)
{
}


void
LoaderFileImpl::get_enum_int (
  const LoaderFileImpl::lfi_path_type&   path_type,
  ::libs::helpers::files::NodeEnumFiles& enum_files,
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
  U3_CHECK (::libs::helpers::files::is_folder (root), "root not dir" + root);

  constexpr auto sub_folders = ::libs::helpers::files::IncludeSubFolders::enabled;
  constexpr auto files       = ::libs::helpers::files::IncludeFiles::enabled;
  constexpr auto recur       = ::libs::helpers::files::Recursives::enabled;

  ::libs::helpers::files::get_files (
    root,
    enum_files,
    { sub_folders, files, recur },
    ::libs::helpers::files::DefaultFileMask (mask));
}


bool
LoaderFileImpl::is_exist_file_int (
  const std::string&                   file_name,
  const LoaderFileImpl::lfi_path_type& path_type) const
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
  const auto file_path = ::libs::helpers::files::make_path (dir_path, file_name);
  return ::libs::helpers::files::is_file_exist (file_path);
}


bool
LoaderFileImpl::is_exist_folder_int (
  const std::string&                   file_name,
  const LoaderFileImpl::lfi_path_type& path_type) const
{
  return is_exist_file_int (file_name, path_type);
}


bool
LoaderFileImpl::get_int (
  const std::string&                    file_name,
  const LoaderFileImpl::lfi_path_type&  path_type,
  ::libs::helpers::mem::IBlockMem::ptr& ret)
{
  const auto dir_path  = iinfo_.paths_->get_path (path_type);
  const auto file_path = ::libs::helpers::files::make_path (dir_path, file_name);
  return ::libs::helpers::files::load_file2mem (file_path, ret);
}
}   // namespace libs::iproperties::xml::general
