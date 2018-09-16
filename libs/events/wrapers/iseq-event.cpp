//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       iseq-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "iseq-event.hpp"

namespace libs { namespace events {

ISeqEvent::ISeqEvent (const Acessor& _ph, IEvent::ptr _int, const id_type& _id) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), _int),
  id_ (_id)
{
  property_name_ = gen_get_mid ();
}


ISeqEvent::~ISeqEvent ()
{}


IEvent::ptr
ISeqEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ISeqEvent> (this, _deep);
}


const ISeqEvent::id_type&
ISeqEvent::get_seq_id () const
{
  UASSERT (!id_.empty ());
  return id_;
}


void
ISeqEvent::set_seq_id (const id_type& _id)
{
  id_ = _id;
  return;
}


bool
ISeqEvent::empty () const
{
  return id_.empty ();
}


void
ISeqEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ISeqEvent);
  super::copy_int (_src);
  id_ = _dsrc->id_;
  return;
}


template <class Archive>
void
ISeqEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_);
  return;
}

}}      // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISeqEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::ISeqEvent);
