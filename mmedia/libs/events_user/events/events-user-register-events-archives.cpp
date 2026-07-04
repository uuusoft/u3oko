/**
\file       events-user-register-events-archives.cpp
\date       21.06.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "events-user-register-events-archives.hpp"

namespace libs::events_user::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_user::events::BaseUserEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_user::events::GetUsersSessions > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_user::events::GetUsersList > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_user::events::WrapperUserEvent > ();
}
}   // namespace libs::events_user::events
