//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       load_compound_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_lib_helpers
\brief      empty brief
*/

namespace libs { namespace icore { namespace xml { namespace helpers {
/**
\brief          Вспомогательная функция для загрузки xml файла.
\param[in,out]  _loader       системно зависимая реализация загрузчика xml  в заданный блок памяти из заданного "файла".
\param[in]      _file_name    имя "файла".
\param[in]      _storage_type тип хранилища, которому принадлежит "файл". Например, конфигурация графа обработки данных, конфигурация страницы графического интерфейса и т.п.
\param[out]     _xml_doc      выходной xml документ.
*/
inline void
load_xml (
  Loader::raw_ptr     _loader,
  const std::string&  _file_name,
  const TypePath&     _storage_type,
  pugi::xml_document& _xml_doc)
{
  ::utils::mem_functs::IBlockMem::ptr _bmem;
  _loader->load (_file_name, _storage_type, _bmem);
  CHECK_CALL (_xml_doc.load_buffer (_bmem->get (), _bmem->get_data_size ()), (std::string ("failed load xml, ") + _file_name).c_str ());
  return;
}

}}}}      // namespace libs::icore::xml::helpers
