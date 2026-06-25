#pragma once
/**
\file       load-save-file-event-funcs.hpp
\date       04.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::appl::helpers
{
void save_event_to_bin_file (const std::string&, ::libs::events::IEvent::ptr&);
void save_event_to_json_file (const std::string&, ::libs::events::IEvent::ptr&);
void load_event_from_bin_file (const std::string&, ::libs::events::IEvent::ptr&);
void load_event_from_json_file (const std::string&, ::libs::events::IEvent::ptr&);
}   // namespace libs::ilink::appl::helpers
