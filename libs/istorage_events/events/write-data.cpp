//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       write-data.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "write-data.hpp"

namespace libs { namespace istorage_events { namespace events {

WriteData::WriteData (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


WriteData::~WriteData ()
{}


void
WriteData::set_stream_id (const stream_id_type& _id)
{
  stream_id_ = _id;
  return;
}


const stream_id_type&
WriteData::get_stream_id () const
{
  return stream_id_;
}


void
WriteData::set_msg (::libs::events::IEvent::ptr& _buff)
{
  buff_ = _buff;
  return;
}


::libs::events::IEvent::ptr
WriteData::get_msg () const
{
  return buff_;
}


::libs::events::IEvent::ptr
WriteData::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<WriteData> (this, _deep);
}


void
WriteData::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (WriteData);
  super::copy_int (_src);
  stream_id_ = _dsrc->stream_id_;
  buff_      = _dsrc->buff_;
  return;
}


template <class Archive>
void
WriteData::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (stream_id_);
  ar& BOOST_SERIALIZATION_NVP (buff_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::WriteData);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::WriteData);
