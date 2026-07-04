/**
\file       get-users-list.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2026
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "get-users-list.hpp"

namespace libs::events_user::events
{
GetUsersList::GetUsersList (const Acessor& pha, const users_list_type& users_ids) :
  users_ids_ (users_ids)
{
}


auto
GetUsersList::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetUsersList::gen_get_mid ();
}


auto
GetUsersList::get_users_ids () const -> const users_list_type&
{
  return users_ids_;
}


::libs::events::IEvent::ptr
GetUsersList::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetUsersList > (this, deep);
}


void
GetUsersList::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetUsersList > (src);
  super::copy_int (src);

  users_ids_ = dsrc->users_ids_;
}


template< class Archive >
void
GetUsersList::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_useroeventsoBaseUserEvent", super);
  arh& BOOST_SERIALIZATION_NVP (users_ids_);

  self_correct ();
}
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_user::events::GetUsersList);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_user::events::GetUsersList);
