/**
\file       load-save-file-event-funcs.cpp
\date       04.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "load-save-file-event-funcs.hpp"

namespace libs::ilink::appl::helpers
{
void
save_event_to_bin_file (const std::string& path2folder, ::libs::events::IEvent::ptr& smsg)
{
  const auto id_event   = smsg->get_mid ();
  const auto event_file = ::libs::utility::files::make_path (path2folder, ::libs::utility::files::prepare_for_file_name (id_event));

  std::ofstream ofs (event_file, std::ios_base::binary);
  ::libs::iproperties::helpers::event2bin (smsg, ofs);
}


void
save_event_to_json_file (const std::string& path2folder, ::libs::events::IEvent::ptr& smsg)
{
  const auto id_event   = smsg->get_mid ();
  const auto event_file = ::libs::utility::files::make_path (path2folder, ::libs::utility::files::prepare_for_file_name (id_event));

  std::ofstream ofs (event_file, std::ios_base::binary);
  ofs << smsg->save_json ();
}


void
load_event_from_bin_file (const std::string& path2folder, ::libs::events::IEvent::ptr& dmsg)
{
  const auto    id_event  = dmsg->get_mid ();
  const auto    path2file = ::libs::utility::files::make_path (path2folder, ::libs::utility::files::prepare_for_file_name (id_event));
  std::ifstream ifs (path2file, std::ios_base::binary);

  if (ifs.is_open ())
  {
    ::libs::events::IEvent::ptr msg;
    ::libs::iproperties::helpers::bin2event (ifs, msg);
    U3_CHECK (msg, "empty loaded msg" + TOLOG (path2folder));
    dmsg->copy (msg.get ());
  }
}


void
load_event_from_json_file (const std::string& path2folder, ::libs::events::IEvent::ptr& dmsg)
{
  const auto    id_event  = dmsg->get_mid ();
  const auto    path2file = ::libs::utility::files::make_path (path2folder, ::libs::utility::files::prepare_for_file_name (id_event));
  std::ifstream ifs (path2file, std::ios_base::binary);

  if (ifs.is_open ())
  {
    std::string temp_json;
    ifs >> temp_json;
    dmsg->load_json (temp_json);
  }
}
}   // namespace libs::ilink::appl::helpers
