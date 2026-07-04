/**
\file       user-id-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "user-id-event.hpp"

namespace libs::events_base
{
UserIdEvent::UserIdEvent (
  const Acessor&              pha,
  const user_id_type&         user_id,
  const user_session_id_type& session) :
  user_id_ (user_id),
  user_session_id_ (session)
{
}


auto
UserIdEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return UserIdEvent::gen_get_mid ();
}


auto
UserIdEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< UserIdEvent > (this, deep);
}


auto
UserIdEvent::set_user_id (user_id_type user_id) -> void
{
  user_id_ = std::move (user_id);
}


auto
UserIdEvent::get_user_id () const -> const user_id_type&
{
  return user_id_;
}


auto
UserIdEvent::set_user_session_id (user_session_id_type user_session_id) -> void
{
  user_session_id_ = std::move (user_session_id);
}


auto
UserIdEvent::get_user_session_id () const -> const user_session_id_type&
{
  return user_session_id_;
}


void
UserIdEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< UserIdEvent > (src);
  super::copy_int (src);
  user_id_         = dsrc->user_id_;
  user_session_id_ = dsrc->user_session_id_;
}

#if 0
void
UserIdEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  user_id_         = ::libs::utility::utils::cuuid_from_string (obj.at ("user_id").as_string ().c_str ());
  user_session_id_ = ::libs::utility::json::get_string (obj.at ("user_session_id").as_string ());
}


void
UserIdEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["user_id"]         = ::libs::utility::utils::to_string (user_id_);
  obj["user_session_id"] = ::libs::utility::utils::to_string (user_session_id_);
}
#endif

template< class Archive >
void
UserIdEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", ::libs::events_base::Event);
  arh& BOOST_SERIALIZATION_NVP (user_id_);
  arh& BOOST_SERIALIZATION_NVP (user_session_id_);

  self_correct ();
}
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::UserIdEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::UserIdEvent);
