/**
\file       loader.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-iproperties-xml-includes_int.hpp"
#include "loader.hpp"

namespace libs::iproperties::xml
{
Loader::Loader (const InitLoaderInfo& info) :
  iinfo_ (info)
{
#ifdef U3_OS_WIN32_DESKTOP
  impl_ = ::std::make_shared< general::LoaderFileImpl > (iinfo_);
#elif defined(U3_OS_GNU_LINUX)
  impl_ = ::std::make_shared< general::LoaderFileImpl > (iinfo_);
#elif defined(U3_OS_RASPBERRY)
  impl_ = ::std::make_shared< general::LoaderFileImpl > (iinfo_);
#elif defined(U3_OS_ORANGE_PI)
  impl_ = ::std::make_shared< general::LoaderFileImpl > (iinfo_);
#elif defined(U3_OS_ANDROID)
  impl_ = ::std::make_shared< android::LoaderAssetAndroidImpl > (iinfo_);
#elif defined(U3_OS_MACX_DESKTOP)
  impl_ = ::std::make_shared< general::LoaderFileImpl > (iinfo_);
#else
#  error select OS
#endif
}


bool
Loader::is_file_exist (
  const std::string&       file_name,
  const appl_paths::Paths& path_type) const
{
  return impl_->is_exist_file (file_name, path_type);
}


bool
Loader::is_folder_exist (
  const std::string&       file_name,
  const appl_paths::Paths& path_type) const
{
  return impl_->is_exist_folder (file_name, path_type);
}


void
Loader::load (
  const std::string&                    file_name,
  const appl_paths::Paths&              path_type,
  ::libs::helpers::mem::IBlockMem::ptr& bmem)
{
  try
  {
    U3_ASSERT (!file_name.empty ());
    U3_CHECK (impl_->get (file_name, path_type, bmem), ("load file: " + file_name).c_str ());
    // U3_CHECK( bmem->get() && bmem->get_data_size(), ("load file, empty bmem,"  + file_name ).c_str() );
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (std::string ("exception Loader::load:") + excpt.what ());
  }
}


void
Loader::get_enum (
  const appl_paths::Paths&               path_type,
  ::libs::helpers::files::NodeEnumFiles& fenum,
  const std::string&                     mask)
{
  U3_XLOG_DBG ("Loader::get_enum" + TOLOG (to_string (path_type)) + VTOLOG (iinfo_.disable_change_search_rule_));
  impl_->get_enum (path_type, fenum, mask);
  if (iinfo_.disable_change_search_rule_)
  {
    return;
  }

  bool disable_recursive = false;
  bool disable_files     = false;

  switch (path_type)
  {
  case appl_paths::Paths::active_data_module:
    disable_recursive = true;
    disable_files     = true;
    break;
  case appl_paths::Paths::generic_appl:
  case appl_paths::Paths::logs:
  case appl_paths::Paths::main_appl:
  case appl_paths::Paths::bins:
  case appl_paths::Paths::emulate_bins:
  case appl_paths::Paths::templates:
  case appl_paths::Paths::templates_appl_module:
  case appl_paths::Paths::templates_data_module:
  case appl_paths::Paths::templates_gui_module:
  case appl_paths::Paths::templates_event_module:
  case appl_paths::Paths::templates_storage_module:
  case appl_paths::Paths::templates_http_module:
  case appl_paths::Paths::active_configs:
  case appl_paths::Paths::active_appl_module:
  case appl_paths::Paths::active_event_module:
  case appl_paths::Paths::active_storage_module:
  case appl_paths::Paths::temp:
  case appl_paths::Paths::debug_test:
  case appl_paths::Paths::unknown:
    // skip compiler warnings
    break;
  }

  std::size_t deep_recursive = 0;

  xml::helpers::enum_files_function (
    fenum,
    "",
    [&deep_recursive, &disable_recursive, &disable_files] (::libs::helpers::files::NodeEnumFiles& node, const std::string& add_root) {
      if (disable_files)
      {
        node.files_.clear ();
      }

      if (disable_recursive && deep_recursive)
      {
        node.folders_.clear ();
      }

      ++deep_recursive;
      return;
    });
}
}   // namespace libs::iproperties::xml
