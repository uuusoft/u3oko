//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       node-path-info.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "node-path-info.hpp"

namespace libs { namespace imdata_events { namespace events {

NodePathInfo::NodePathInfo (const std::string& _id, const std::string& _name_dll) :
  id_ (_id),
  name_dll_ (_name_dll)
{}


NodePathInfo::~NodePathInfo ()
{}


bool
NodePathInfo::check () const
{
  return id_.empty () || name_dll_.empty () ? false : true;
}


std::string&
NodePathInfo::update_id ()
{
  return id_;
}


std::string&
NodePathInfo::update_name_dll ()
{
  return name_dll_;
}


template <class Archive>
void
NodePathInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (id_);
  ar& BOOST_SERIALIZATION_NVP (name_dll_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::NodePathInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::NodePathInfo);
