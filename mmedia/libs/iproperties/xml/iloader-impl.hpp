#pragma once
/**
\file       iloader-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.10.2016
\project    u3_iproperties_lib
*/

namespace libs::iproperties::xml
{
/// Интерфейс, который должна предоставлять реализация от ОС для загрузки содержимого файлов настройки read-only в память
class ILoaderImpl
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ILoaderImpl)

  virtual ~ILoaderImpl ();

  bool is_exist_file (const std::string&, const appl_paths::Paths&) const;
  bool is_exist_folder (const std::string&, const appl_paths::Paths&) const;
  /// Функция загрузки содержимого файла в память
  /// \param[in]  file_name    имя файла
  /// \param[in]  storage_type тип хранилища, в котором находится файл
  /// \param[out] ret          блок памяти, с содержимом файла
  /// \return     true, при успехе
  bool get (
    const std::string&                    file_name,
    const appl_paths::Paths&              storage_type,
    ::libs::helpers::mem::IBlockMem::ptr& ret);

  void get_enum (
    const appl_paths::Paths&               storage_type,
    ::libs::helpers::files::NodeEnumFiles& fenum,
    const std::string&                     mask);

  protected:
  ILoaderImpl ();

  private:
  //  ILoaderImpl interface
  virtual bool is_exist_file_int (const std::string&, const appl_paths::Paths&) const                              = 0;
  virtual bool is_exist_folder_int (const std::string&, const appl_paths::Paths&) const                            = 0;
  virtual bool get_int (const std::string&, const appl_paths::Paths&, ::libs::helpers::mem::IBlockMem::ptr&)       = 0;
  virtual void get_enum_int (const appl_paths::Paths&, ::libs::helpers::files::NodeEnumFiles&, const std::string&) = 0;
};
}   // namespace libs::iproperties::xml
