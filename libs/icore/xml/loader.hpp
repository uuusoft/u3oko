#pragma once
/**
\file       loader.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.10.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace xml {
//  syn
using ::libs::iproperties::appl_paths::TypePath;
using ::libs::iproperties::appl_paths::IAppPaths;
using ::utils::mem_functs::IBlockMem;
using ::libs::helpers::files::NodeEnumFiles;
/**
\brief  Тип для группировки данных для инициализации Loader.
*/
struct TInitInfo
{
  explicit TInitInfo (IAppPaths::cptr _paths) :
    paths_ (_paths)
  {}

  IAppPaths::cptr paths_;      //< Указатель на хранилище путей к различным ресурсам.
};
/**
\brief  Тип для загрузки унифицированной загрузки константных ресурсов (скриптов, файлов и прочего).
        Обеспечивает унифицированную работу с ними, вне зависимости от ОС.
*/
class Loader
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (Loader);

  explicit Loader (const TInitInfo& _info);

  void load (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _bmem);

  void get_enum (const TypePath& _storage_type, NodeEnumFiles& _enum);


  private:
  TInitInfo        iinfo_;      //< Информация инициализации объекта.
  ILoaderImpl::ptr impl_;       //< Выбранная реализация для работы на данным момент в данной ОС.
};

}}}      // namespace libs::icore::xml
