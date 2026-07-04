#pragma once
/**
\file       loader-asset-android-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/
#ifdef U3_OS_ANDROID

namespace libs::iproperties::xml::android
{
/// Реализация загрузчика неизменяемых файлов из комлпекта поставки системы для Android
class LoaderAssetAndroidImpl final : public ILoaderImpl
{
  public:
  explicit LoaderAssetAndroidImpl (const InitLoaderInfo& info);
  virtual ~LoaderAssetAndroidImpl ();

  private:
  //  ILoaderImpl overrides
  virtual bool is_exist_file_int (const std::string&, const appl_paths::Paths&) const override;
  virtual bool is_exist_folder_int (const std::string&, const appl_paths::Paths&) const override;
  virtual void get_enum_int (const appl_paths::Paths&, ::libs::utility::files::NodeEnumFiles&, const std::string&) override;
  virtual bool get_int (const std::string&, const appl_paths::Paths&, ::libs::utility::mem::IBlockMem::ptr&) override;

  // internals
  void enum_items_struct (const std::string&, const std::string&, ::libs::utility::files::NodeEnumFiles&);
  bool storage_not_in_asset (const appl_paths::Paths&) const;

  InitLoaderInfo                 iinfo_;                     //<
  AAssetManager*                 asset_manager_ = nullptr;   //<
  AAssetDir*                     aroot_         = nullptr;   //<
  std::unique_ptr< ILoaderImpl > common_impl_;               //< Некоторые данные находятся на диске, поэтому используем общую реализацию
};
}   // namespace libs::iproperties::xml::android

#endif
