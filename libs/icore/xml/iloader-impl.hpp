#pragma once
/**
\file       iloader-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.10.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace xml {
//  syn
using ::libs::iproperties::appl_paths::TypePath;
using ::utils::mem_functs::IBlockMem;
using ::libs::helpers::files::NodeEnumFiles;
/**
\brief  Интерфейс, который должна предоставлять реализация от ОС для загрузки содержимого файлов настройки read-only в память.
*/
class ILoaderImpl
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ILoaderImpl);

  virtual ~ILoaderImpl ()
  {}
  /**
  \brief      Функция загрузки содержимого файла в память.
  \param[in]  _file_name    имя файла.
  \param[in]  _storage_type тип хранилища, в котором находится файл.
  \param[out] _ret          блок памяти, с содержимом файла.
  \return     true, при успехе.
  */
  bool
  get (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret)
  {
    return get_int (_file_name, _storage_type, _ret);
  }

  void
  get_enum (const TypePath& _storage_type, NodeEnumFiles& _enum)
  {
    return get_enum_int (_storage_type, _enum);
  }


  protected:
  ILoaderImpl ()
  {}


  private:
  //  ILoaderImpl interface
  virtual bool get_int (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret) = 0;
  virtual void get_enum_int (const TypePath& _storage_type, NodeEnumFiles& _enum)                           = 0;
};

}}}      // namespace libs::icore::xml
