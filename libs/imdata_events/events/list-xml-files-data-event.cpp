//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       list-xml-files-data-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "list-xml-files-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

ListXmlFilesDataEvent::ListXmlFilesDataEvent (const Acessor& _ph, const xml_files_type& _xml_files) :
  xml_files_ (_xml_files)
{
  property_name_ = gen_get_mid ();
}


ListXmlFilesDataEvent::~ListXmlFilesDataEvent ()
{
}


const ListXmlFilesDataEvent::xml_files_type&
ListXmlFilesDataEvent::get_xml_files () const
{
  return xml_files_;
}


void
ListXmlFilesDataEvent::set_xml_files (ListXmlFilesDataEvent::xml_files_type&& _src)
{
  std::swap (xml_files_, _src);
  return;
}


::libs::events::IEvent::ptr
ListXmlFilesDataEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ListXmlFilesDataEvent> (this, _deep);
}


void
ListXmlFilesDataEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);
  self_correct ();
  return;
}


void
ListXmlFilesDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ListXmlFilesDataEvent);
  super::copy_int (_src);
  xml_files_ = _dsrc->xml_files_;
  return;
}


template <class Archive>
void
ListXmlFilesDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (xml_files_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ListXmlFilesDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::ListXmlFilesDataEvent);
