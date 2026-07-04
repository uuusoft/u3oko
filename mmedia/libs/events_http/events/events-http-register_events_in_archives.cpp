/**
\file       events-http-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_http
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "events-http-register_events_in_archives.hpp"

namespace libs::events_http::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_http::events::BaseHttpEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_http::events::WrapperHttpEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_http::events::MemResourceHttpEvent > ();
}
}   // namespace libs::events_http::events
