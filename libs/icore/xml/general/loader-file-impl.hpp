#pragma once
/**
\file       loader-file-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace xml { namespace general {
//  syn
using ::libs::helpers::files::NodeEnumFiles;
/**
\brief  Общая реализация загрузчика неизменяемых файлов из комлпекта поставки системы.
        Используется по умолчанию (win32/linux).
*/
class LoaderFileImpl : public ILoaderImpl
{
  public:
  explicit LoaderFileImpl (const TInitInfo& _info);

  virtual ~LoaderFileImpl ();


  private:
  //  ILoaderImpl overrides
  virtual void get_enum_int (const TypePath& _storage_type, NodeEnumFiles& _enum) override;
  virtual bool get_int (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret) override;

  TInitInfo           iinfo_;          //< Информация, переданная при создании экзепляра.
  NodeEnumFiles       enums_;          //< Список файлов и директорий.
  mutable std::size_t iter_indx_;      //< Индекс итератора перечисления файлов и директорий.
};

}}}}      // namespace libs::icore::xml::general
