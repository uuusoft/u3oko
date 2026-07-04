/**
\file       iseq-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "iseq-event.hpp"

namespace libs::events
{
ISeqEvent::ISeqEvent (const Acessor& pha, IEvent::ptr val, const id_type& id) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), std::move (val)),
  id_ (id)
{
}


auto
ISeqEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ISeqEvent::gen_get_mid ();
}


auto
ISeqEvent::clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return ::libs::events::deep_clone< ISeqEvent > (this, deep);
}


auto
ISeqEvent::get_seq_id () const -> const ISeqEvent::id_type&
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


auto
ISeqEvent::empty () const -> bool
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("IWrapBaseEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISeqEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::ISeqEvent);
