//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path-obj-id.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Реализация идентификатора объекта графа.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "path-obj-id.hpp"

namespace libs { namespace core { namespace path {

PathObjID::PathObjID (const name_id_type& _name, const name_dll_type& _name_dll) :
  id_node_name_ (_name),
  id_node_name_dll_ (_name_dll)
{}


PathObjID::~PathObjID ()
{}


const PathObjID::name_id_type
PathObjID::get_name () const
{
  return id_node_name_;
}


const PathObjID::name_dll_type&
PathObjID::get_name_dll () const
{
  return id_node_name_dll_;
}


bool
PathObjID::operator< (const PathObjID& _obj) const
{
  UASSERT (check ());
  UASSERT (_obj.check ());
  return id_node_name_ < _obj.id_node_name_;
}


bool
PathObjID::check () const
{
  return id_node_name_.empty () ? false : true;
}


template <class Archive>
void
PathObjID::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (id_node_name_);
  ar& BOOST_SERIALIZATION_NVP (id_node_name_dll_);
  return;
}

}}}      // namespace libs::core::path

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::core::path::PathObjID);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::core::path::PathObjID);
