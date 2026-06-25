/**
\file       iseq-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "iseq-event.hpp"

namespace libs::events
{
ISeqEvent::ISeqEvent (const Acessor& pha, IEvent::ptr val, const id_type& id) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), val),
  id_ (id)
{
  property_name_ = gen_get_mid ();
}


IEvent::ptr
ISeqEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ISeqEvent > (this, deep);
}


const ISeqEvent::id_type&
ISeqEvent::get_seq_id () const
{
  U3_ASSERT (!id_.empty ());
  return id_;
}


void
ISeqEvent::set_seq_id (const id_type& id)
{
  U3_ASSERT (!id.empty ());
  id_ = id;
}


bool
ISeqEvent::empty () const
{
  return id_.empty ();
}


void
ISeqEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ISeqEvent > (src);
  super::copy_int (src);
  id_ = dsrc->id_;
}


template< class Archive >
void
ISeqEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("IWrapBaseEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISeqEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::ISeqEvent);
