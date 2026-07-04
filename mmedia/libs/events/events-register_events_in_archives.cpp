/**
\file       events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "includes_int.hpp"
#include "events-register_events_in_archives.hpp"

namespace libs::events
{
void
register_events_in_archives ()
{
  libs::iproperties::helpers::make_stub_obj< ::libs::events::IAnswerEvent > ();
  libs::iproperties::helpers::make_stub_obj< ::libs::events::IRequestEvent > ();
  libs::iproperties::helpers::make_stub_obj< ::libs::events::ISeqEvent > ();
  libs::iproperties::helpers::make_stub_obj< ::libs::events::ISyncEvent > ();
  libs::iproperties::helpers::make_stub_obj< ::libs::events::IWrapBaseEvent > ();
}
}   // namespace libs::events
