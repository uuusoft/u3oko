#pragma once
/**
\file       load_compound_types.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_lib_helpers
*/

namespace libs::iproperties::xml::helpers
{
/// Вспомогательная функция для загрузки xml файла
/// \param[in,out]  loader       системно зависимая реализация загрузчика xml  в заданный блок памяти из заданного "файла"
/// \param[in]      file_name    имя "файла"
/// \param[in]      storage_type тип хранилища, которому принадлежит "файл". Например, конфигурация графа обработки данных, конфигурация страницы графического интерфейса и т.п
/// \param[out]     xml_doc      выходной xml документ
bool
load_xml (
  Loader::raw_ptr          loader,
  const std::string&       file_name,
  const appl_paths::Paths& storage_type,
  pugi::xml_document&      xml_doc);
}   // namespace libs::iproperties::xml::helpers
