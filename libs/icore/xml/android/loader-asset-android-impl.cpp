//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       loader-asset-android-impl.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "loader-asset-android-impl.hpp"

namespace libs { namespace icore { namespace xml { namespace android {

#if defined(UUU_OS_ANDROID)

LoaderAssetAndroidImpl::LoaderAssetAndroidImpl (const TInitInfo& _info) :
  iinfo_ (_info),
  asset_manager_ (nullptr),
  aroot_ (nullptr)
{
  SystemAndroidProperty*      _osinfo = UUU_PROP_CAST (SystemAndroidProperty*) (::libs::iproperties::helpers::get_spec_prop_os ());
  ISharedProperty::guard_type _guard (_osinfo->get_sync ());
  asset_manager_ = _osinfo->get_aappl_lockfree ()->activity->assetManager;
  CHECK_STATE (asset_manager_, "failed, empty asset_manager_");
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
LoaderAssetAndroidImpl::enum_items_struct (const std::string& _root, const std::string& _name, NodeEnumFiles& _enum_files)
{
  _enum_files.clear ();
  _enum_files.name_ = _name;

  const std::string _cur_root   = ::libs::helpers::files::make_path (_root, _name);
  AAssetDir*        _cur_folder = AAssetManager_openDir (asset_manager_, _cur_root.c_str ());

  CHECK_STATE (_cur_folder, "failed, open asset dir, " + _cur_root);
  XULOG_TRACE ("LoaderAssetAndroidImpl::enum_items_struct, cur_root=" << _cur_root);

  AAssetDir_rewind (_cur_folder);

  do
    {
      const char* _raw_name_item = AAssetDir_getNextFileName (_cur_folder);
      if (!_raw_name_item)
        {
          break;
        }

      bool              _it_folder       = false;
      std::string       _name_item       = _raw_name_item;
      const std::string _sign_folder     = ".dir";
      std::size_t       _off_sign_folder = _name_item.find (_sign_folder);

      if (std::string::npos != _off_sign_folder)
        {
          _it_folder = true;
          _name_item.erase (_name_item.length () - _sign_folder.length (), std::string::npos);
        }

      const std::string _path_item = ::libs::helpers::files::make_path (_cur_root, _name_item);
      UASSERT (!_name_item.empty ());
      XULOG_TRACE ("LoaderAssetAndroidImpl::enum_items_struct, _path_item=" << _path_item);

      if (_it_folder)
        {
          AAssetDir* _check_folder = AAssetManager_openDir (asset_manager_, _path_item.c_str ());

          if (_check_folder)
            {
              AAssetDir_close (_check_folder);
              _check_folder = nullptr;
              _enum_files.folders_.push_back (NodeEnumFiles ());
              enum_items_struct (_cur_root, _name_item, _enum_files.folders_.back ());
            }
        }
      else if (AAsset* _check_file = AAssetManager_open (asset_manager_, _path_item.c_str (), AASSET_MODE_UNKNOWN))
        {
          _enum_files.files_.push_back (_name_item);
          AAsset_close (_check_file);
          _check_file = nullptr;
        }
      else
        {
          UASSERT_SIGNAL (("failed, unknown type item, " + _path_item).c_str ());
        }
    }
  while (true);
  AAssetDir_close (_cur_folder);
  return;
}


void
LoaderAssetAndroidImpl::get_enum_int (const TypePath& _storage_type, NodeEnumFiles& _enum_files)
{
  const std::string _root = iinfo_.paths_->get_path (_storage_type);
  enum_items_struct (_root, "", _enum_files);
  return;
}


bool
LoaderAssetAndroidImpl::get_int (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret)
{
  UASSERT (!_file_name.empty ());
  UASSERT (!_ret);
  _ret.reset ();

  const std::string _root      = iinfo_.paths_->get_path (_storage_type);
  const std::string _file_path = ::libs::helpers::files::make_path (_root, _file_name);
  AAsset*           _dbuff     = AAssetManager_open (asset_manager_, _file_path.c_str (), AASSET_MODE_UNKNOWN);

  if (!_dbuff)
    {
      XULOG_TRACE ("LoaderAssetAndroidImpl::get::failed open buff");
      XULOG_TRACE (_file_path);
      UASSERT_SIGNAL ("failed");
      //void AAssetDir_close(AAssetDir* assetDir);
      return false;
    }

  const off_t _size = AAsset_getLength (_dbuff);
  _ret              = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (_size + 1);

  const int _bread = AAsset_read (_dbuff, _ret->get (), _size);
  if (_bread != _size)
    {
      UASSERT_SIGNAL ("failed");
      AAsset_close (_dbuff);
      return false;
    }

  ::utils::mem_functs::helpers::get_as<char> (_ret.get ())[_size] = '\0';
  _ret->set_data_size (_size);
  AAsset_close (_dbuff);
  return true;
}

#endif

}}}}      // namespace libs::icore::xml::android
