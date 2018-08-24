//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       update-stream.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "update-stream.hpp"

namespace libs { namespace istorage_events { namespace events {

UpdateStream::UpdateStream (const Acessor& _ph) :
  operation_ (TypeActionStream::read),
  direction_ (TypeDirectionStream::unknown)
{
  property_name_ = gen_get_type_text_id ();
}


UpdateStream::~UpdateStream ()
{}


::libs::events::IEvent::ptr
UpdateStream::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<UpdateStream> (this, _deep);
}


void
UpdateStream::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (UpdateStream);
  super::copy_int (_src);
  obj_id_    = _dsrc->obj_id_;
  stream_id_ = _dsrc->stream_id_;
  action_    = _dsrc->action_;
  direction_ = _dsrc->direction_;
  time_      = _dsrc->time_;
  operation_ = _dsrc->operation_;
  return;
}


template <class Archive>
void
UpdateStream::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (obj_id_);
  ar& BOOST_SERIALIZATION_NVP (operation_);
  ar& BOOST_SERIALIZATION_NVP (stream_id_);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (direction_);
  ar& BOOST_SERIALIZATION_NVP (time_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::UpdateStream);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::UpdateStream);
