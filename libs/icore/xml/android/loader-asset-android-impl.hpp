#pragma once
/**
\file       loader-asset-android-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace xml { namespace android {

#if defined(UUU_OS_ANDROID)
//  syn
using ::libs::iproperties::vers::system::SystemAndroidProperty;
using ::libs::properties::ISharedProperty;
using ::libs::iproperties::appl_paths::TypePath;
using ::utils::mem_functs::IBlockMem;
/**
\brief  Реализация загрузчика неизменяемых файлов из комлпекта поставки системы для Android.
*/
class LoaderAssetAndroidImpl : public ILoaderImpl
{
  public:
  explicit LoaderAssetAndroidImpl (const TInitInfo& _info);

  virtual ~LoaderAssetAndroidImpl ();


  private:
  //  ILoaderImpl overrides
  virtual void get_enum_int (const TypePath& _storage_type, NodeEnumFiles& _enum) override;
  virtual bool get_int (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret) override;

  void enum_items_struct (const std::string& _root, const std::string& _name, NodeEnumFiles& _enum_files);

  TInitInfo      iinfo_;              //< ???
  AAssetManager* asset_manager_;      //< ???
  AAssetDir*     aroot_;              //< ???
};
#endif

}}}}      // namespace libs::icore::xml::android
