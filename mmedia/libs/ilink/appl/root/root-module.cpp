/**
\file       root-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "root-module.hpp"

namespace libs::ilink::appl::root
{
RootModule::RootModule () :
  seqs_ ([] (const StateProcessEventExt& left, const StateProcessEventExt& right) -> bool { return left.id_seq_ < right.id_seq_; })
{
}


auto
RootModule::get_dest_link (syn::IEvent::ptr& msg) -> ::libs::link::ILink::ptr
{
  U3_ASSERT (!current_seq_.dest_);
  //  Самые частые сообщения к основному модулю, т.к. фактически через него общаются друг с другом все другие модули.
  if (::libs::iproperties::helpers::cast_event< ::libs::events_media::events::BaseDataEvent > (msg))
  {
    U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2mdata");
    return links_[syn::mids::appl2mdata];
  }
  //  Далее идут сообщения логирования.
  if (::libs::iproperties::helpers::cast_event< ::libs::events_log::events::BaseLogEvent > (msg))
  {
    // U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2log");
    return links_[syn::mids::appl2log];
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::events_storage::events::BaseStorageEvent > (msg))
  {
    // U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2storage");
    return links_[syn::mids::appl2storage];
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::events_msg::events::BaseEventsMsg > (msg))
  {
    U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2events");
    return links_[syn::mids::appl2events];
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::events_http::events::BaseHttpEvent > (msg))
  {
    // U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2http");
    return links_[syn::mids::appl2http];
  }
#if (U3_MODULES_ENABLE_GUI == 1)
  if (::libs::iproperties::helpers::cast_event< ::libs::events_gui::events::BaseGUIEvent > (msg))
  {
    U3_XLOG_DBG ("RootModule::get_dest_link:: select appl2gui");
    return links_[syn::mids::appl2gui];
  }
#endif
  // EAI-REFACT
  // U3_XLOG_WARN ("RootModule::get_dest_link:: select unknown");
  return {};
}
}   // namespace libs::ilink::appl::root
