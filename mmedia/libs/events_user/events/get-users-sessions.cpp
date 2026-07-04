/**
\file       get-users-sessions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "get-users-sessions.hpp"

namespace libs::events_user::events
{
GetUsersSessions::GetUsersSessions (const Acessor& pha, const syn::user_id_type& user_id) :
  user_id_ (user_id)
{
}


auto
GetUsersSessions::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetUsersSessions::gen_get_mid ();
}


auto
GetUsersSessions::set_user_id (user_id_type user_id) -> void
{
  user_id_ = std::move (user_id);
}


auto
GetUsersSessions::get_user_id () const -> const user_id_type&
{
  return user_id_;
}


auto
GetUsersSessions::get_sessions () -> const sessions_users_type&
{
  return sessions_;
}


auto
GetUsersSessions::set_sessions (const sessions_users_type& sessions) -> void
{
  sessions_ = sessions;
}


::libs::events::IEvent::ptr
GetUsersSessions::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetUsersSessions > (this, deep);
}


void
GetUsersSessions::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetUsersSessions > (src);
  super::copy_int (src);

  sessions_ = dsrc->sessions_;
}


template< class Archive >
void
GetUsersSessions::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_useroeventsoBaseUserEvent", super);
  arh& BOOST_SERIALIZATION_NVP (sessions_);

  self_correct ();
}
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_user::events::GetUsersSessions);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_user::events::GetUsersSessions);
