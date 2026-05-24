/**
\file       load_compound_types.cpp
\date       22.02.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_lib_helpers
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-iproperties-xml-includes_int.hpp"

namespace libs::iproperties::xml::helpers
{
bool
load_xml (
  Loader::raw_ptr          loader,
  const std::string&       file_name,
  const appl_paths::Paths& storage_type,
  pugi::xml_document&      xml_doc)
{
  ::libs::helpers::mem::IBlockMem::ptr bmem;
  loader->load (file_name, storage_type, bmem);

  if (!bmem.get () || 0 == bmem->get_data_size ())
  {
    return false;
  }

  U3_XLOG_DEV ("WTF xml_doc.load_buffer doing?");
  return xml_doc.load_buffer (bmem->get (), bmem->get_data_size ()), (std::string ("load xml, ") + file_name).c_str ();
}
}   // namespace libs::iproperties::xml::helpers
