/**
\file       loader-asset-android-impl.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "../libs-iproperties-xml-includes_int.hpp"
#include "loader-asset-android-impl.hpp"

#ifdef U3_OS_ANDROID

namespace libs::iproperties::xml::android
{
LoaderAssetAndroidImpl::LoaderAssetAndroidImpl (const InitLoaderInfo& info) :
  iinfo_ (info),
  asset_manager_ (nullptr),
  aroot_ (nullptr),
  common_impl_ (std::make_unique< xml::general::LoaderFileImpl > (info))
{
  auto*                           osinfo = ::libs::utility::casts::reinterpret_cast_helper< vers::system::SystemAndroidProperty* > (::libs::iproperties::helpers::get_spec_prop_os ());
  syn::ISharedProperty::lock_type lock (osinfo->get_sync ());

  asset_manager_ = osinfo->get_aappl_lockfree ()->activity->assetManager;
  U3_CHECK (asset_manager_, "empty asset_manager_");
}


LoaderAssetAndroidImpl::~LoaderAssetAndroidImpl ()
{
  if (aroot_)
  {
    AAssetDir_close (aroot_);
    aroot_ = nullptr;
  }
}

void
LoaderAssetAndroidImpl::enum_items_struct (
  const std::string&                     root,
  const std::string&                     name,
  ::libs::utility::files::NodeEnumFiles& enum_files)
{
  enum_files.clear ();
  enum_files.name_ = name;

  const std::string cur_root   = ::libs::utility::files::make_path (root, name);
  AAssetDir*        cur_folder = AAssetManager_openDir (asset_manager_, cur_root.c_str ());

  U3_XLOG_MARK ("LoaderAssetAndroidImpl::enum_items_struct enum asset struct from" + TOLOG (cur_root))
  U3_CHECK (cur_folder, "open asset folder " + cur_root);

  AAssetDir_rewind (cur_folder);
  do
  {
    const char* raw_name_item = AAssetDir_getNextFileName (cur_folder);
    if (!raw_name_item)
    {
      break;
    }

    bool              it_folder       = false;
    std::string       name_item       = raw_name_item;
    const std::string sign_folder     = ".dir";
    std::size_t       off_sign_folder = name_item.find (sign_folder);

    if (std::string::npos != off_sign_folder)
    {
      it_folder = true;
      name_item.erase (name_item.length () - sign_folder.length (), std::string::npos);
    }


    const std::string path_item = ::libs::utility::files::make_path (cur_root, name_item);
    U3_XLOG_MARK ("find item in asset struct" + TOLOG (raw_name_item) + TOLOG (name_item) + VTOLOG (it_folder) + TOLOG (path_item))
    U3_ASSERT (!name_item.empty ());

    if (it_folder)
    {
      AAssetDir* check_folder = AAssetManager_openDir (asset_manager_, path_item.c_str ());

      if (check_folder)
      {
        AAssetDir_close (check_folder);
        check_folder = nullptr;
        enum_files.folders_.push_back (::libs::utility::files::NodeEnumFiles ());
        enum_items_struct (cur_root, name_item, enum_files.folders_.back ());
      }
    }
    else if (AAsset* check_file = AAssetManager_open (asset_manager_, path_item.c_str (), AASSET_MODE_UNKNOWN))
    {
      enum_files.files_.push_back (libs::utility::files::FileNode { name_item, 0, 0, U3_CAST_UINT64 (AAsset_getLength64 (check_file)) });
      AAsset_close (check_file);
      check_file = nullptr;
    }
    else
    {
      U3_ASSERT_SIGNAL (("unknown type item " + path_item).c_str ());
    }
  } while (true);

  AAssetDir_close (cur_folder);
}


void
LoaderAssetAndroidImpl::get_enum_int (
  const appl_paths::Paths&               path_type,
  ::libs::utility::files::NodeEnumFiles& enum_files,
  const std::string&                     mask)
{
  U3_XLOG_MARK ("LoaderAssetAndroidImpl::get_enum_int" + TOLOG (to_string (path_type)) + VTOLOG (storage_not_in_asset (path_type)));
  if (storage_not_in_asset (path_type))
  {
    return common_impl_->get_enum (path_type, enum_files, mask);
  }

  const std::string root = iinfo_.paths_->get_path (path_type);
  enum_items_struct (root, "", enum_files);
}


bool
LoaderAssetAndroidImpl::is_exist_file_int (
  const std::string&       file_name,
  const appl_paths::Paths& path_type) const
{
  U3_XLOG_MARK ("LoaderAssetAndroidImpl::is_exist_file_int" + TOLOG (to_string (path_type)) + TOLOG (file_name) + VTOLOG (storage_not_in_asset (path_type)));
  if (storage_not_in_asset (path_type))
  {
    return common_impl_->is_exist_file (file_name, path_type);
  }

  U3_ASSERT (!file_name.empty ());

  const std::string root      = iinfo_.paths_->get_path (path_type);
  const std::string file_path = ::libs::utility::files::make_path (root, file_name);
  AAsset*           dbuf      = AAssetManager_open (asset_manager_, file_path.c_str (), AASSET_MODE_UNKNOWN);
  const bool        ret       = dbuf ? true : false;

  if (dbuf)
  {
    AAsset_close (dbuf);
  }
  return ret;
}


bool
LoaderAssetAndroidImpl::is_exist_folder_int (
  const std::string&       file_name,
  const appl_paths::Paths& path_type) const
{
  if (storage_not_in_asset (path_type))
  {
    return common_impl_->is_exist_folder (file_name, path_type);
  }

  const std::string folder_name = file_name + ".dir";
  return is_exist_file_int (folder_name, path_type);

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  U3_ASSERT (!file_name.empty ());
  const std::string folder_name = file_name;   // + ".dir";
  const std::string root        = iinfo_.paths_->get_path (path_type);
  const std::string file_path   = ::libs::utility::files::make_path (root, folder_name);
  AAssetDir*        dbuf        = AAssetManager_openDir (asset_manager_, file_path.c_str ());

  const bool ret = dbuf ? true : false;
  if (dbuf)
  {
    AAssetDir_close (dbuf);
  }
  return ret;
#  endif
}


bool
LoaderAssetAndroidImpl::get_int (
  const std::string&                    file_name,
  const appl_paths::Paths&              path_type,
  ::libs::utility::mem::IBlockMem::ptr& ret)
{
  if (storage_not_in_asset (path_type))
  {
    U3_XLOG_DEV ("load file, storage not in asset, common path" + TOLOG (file_name) + TOLOG (to_string (path_type)));
    return common_impl_->get (file_name, path_type, ret);
  }

  U3_ASSERT (!file_name.empty ());
  U3_ASSERT (!ret);
  ret.reset ();

  const std::string root      = iinfo_.paths_->get_path (path_type);
  const std::string file_path = ::libs::utility::files::make_path (root, file_name);
  AAsset*           dbuf      = AAssetManager_open (asset_manager_, file_path.c_str (), AASSET_MODE_UNKNOWN);

  if (!dbuf)
  {
    U3_ASSERT_SIGNAL ("failed");
    // void AAssetDir_close(AAssetDir* assetDir);
    return false;
  }

  const off_t size = AAsset_getLength (dbuf);

  ret = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (size + 1);

  const std::int32_t bread = AAsset_read (dbuf, ret->get (), size);
  if (bread != size)
  {
    U3_ASSERT_SIGNAL ("failed");
    AAsset_close (dbuf);
    return false;
  }

  ::utils::mems::helpers::get_as< char > (ret.get ())[size] = '\0';
  ret->set_size (size);
  AAsset_close (dbuf);
  return true;
}


bool
LoaderAssetAndroidImpl::storage_not_in_asset (const appl_paths::Paths& path_type) const
{
  return appl_paths::Paths::active_configs == path_type ||
         appl_paths::Paths::active_appl_module == path_type ||
         appl_paths::Paths::active_data_module == path_type ||
         appl_paths::Paths::active_storage_module == path_type ||
         appl_paths::Paths::active_event_module == path_type ||
         appl_paths::Paths::logs == path_type ||
         appl_paths::Paths::temp == path_type ||
         appl_paths::Paths::bins == path_type ||
         appl_paths::Paths::emulate_bins == path_type;
}
}   // namespace libs::iproperties::xml::android

#endif
