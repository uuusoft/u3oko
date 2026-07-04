/**
\file       process-user-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "process-user-event.hpp"

namespace libs::events_user::events
{
ProcessUserEvent::ProcessUserEvent (
  const Acessor&             ph,
  const id_mem_type&         id,
  const number_mem_buf_type& number)
{
}


auto
ProcessUserEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ProcessUserEvent::gen_get_mid ();
}


#if 0
const ProcessUserEvent::id_mem_type&
ProcessUserEvent::get_id () const
{
  return id_;
}


void
ProcessUserEvent::set_id (const id_mem_type& id)
{
  id_ = id;
}


const ProcessUserEvent::number_mem_buf_type&
ProcessUserEvent::get_numder () const
{
  return number_;
}


void
ProcessUserEvent::set_number (const number_mem_buf_type& number)
{
  number_ = number;
}


bool
ProcessUserEvent::get_request () const
{
  return request_for_transmit_;
}


void
ProcessUserEvent::set_request (bool request)
{
  request_for_transmit_ = request;
}
#endif

::libs::events::IEvent::ptr
ProcessUserEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ProcessUserEvent > (this, deep);
}


void
ProcessUserEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ProcessUserEvent > (src);
  super::copy_int (src);

  // id_                   = dsrc->id_;
  // number_               = dsrc->number_;
  // request_for_transmit_ = dsrc->request_for_transmit_;
}


template< class Archive >
void
ProcessUserEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_useroeventsoBaseUserEvent", super);
  // arh& BOOST_SERIALIZATION_NVP (id_);
  // arh& BOOST_SERIALIZATION_NVP (number_);
  // arh& BOOST_SERIALIZATION_NVP (request_for_transmit_);

  self_correct ();
}
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_user::events::ProcessUserEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_user::events::ProcessUserEvent);
