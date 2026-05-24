#pragma once
/**
\file       loader-file-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::xml::general
{
/// Общая реализация загрузчика неизменяемых файлов из комлпекта поставки системы
/// спользуется по умолчанию (win32/linux)
class LoaderFileImpl final : public ILoaderImpl
{
  public:
  using lfi_path_type = ::libs::iproperties::appl_paths::Paths;

  explicit LoaderFileImpl (const InitLoaderInfo& info);
  virtual ~LoaderFileImpl ();

  private:
  //  ILoaderImpl overrides
  virtual bool is_exist_file_int (const std::string&, const lfi_path_type&) const override;
  virtual bool is_exist_folder_int (const std::string&, const lfi_path_type&) const override;
  virtual void get_enum_int (const lfi_path_type&, ::libs::helpers::files::NodeEnumFiles&, const std::string&) override;
  virtual bool get_int (const std::string&, const lfi_path_type&, ::libs::helpers::mem::IBlockMem::ptr&) override;

  InitLoaderInfo                        iinfo_;   //< нформация, переданная при создании экзепляра
  ::libs::helpers::files::NodeEnumFiles enums_;   //< Список файлов и директорий
};
}   // namespace libs::iproperties::xml::general
