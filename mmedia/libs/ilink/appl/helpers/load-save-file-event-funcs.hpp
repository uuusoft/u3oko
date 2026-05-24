#pragma once
/**
\file       load-save-file-event-funcs.hpp
\date       04.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

namespace libs::ilink::appl::helpers
{
void save_event_to_bin_file (const std::string& path2folder, ::libs::events::IEvent::ptr& smsg);
void save_event_to_json_file (const std::string& path2folder, ::libs::events::IEvent::ptr& smsg);
void load_event_from_bin_file (const std::string& path2folder, ::libs::events::IEvent::ptr& dmsg);
void load_event_from_json_file (const std::string& path2folder, ::libs::events::IEvent::ptr& dmsg);
}   // namespace libs::ilink::appl::helpers
