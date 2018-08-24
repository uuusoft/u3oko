//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_helper_log_calls.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/

#ifndef MSG2LOGGER
#define MSG2LOGGER(_logger, _info, _application_id)                                                                                                 \
  if (_logger)                                                                                                                                      \
    {                                                                                                                                               \
      auto _demons = ::libs::iproperties::helpers::cast_prop_demons (); \
      auto _events = _demons->get_events_lockfree ();                                                                                               \
      if (_events)                                                                                                                                  \
        {                                                                                                                                           \
          auto       _impl   = _events->impl ();                                                                                                    \
          const auto _id     = ::libs::ilog_events::events::InfoLogEvent::gen_get_type_text_id ();                                                  \
          auto       _revent = _impl->get (_id);                                                                                                    \
          auto       _levent = UUU_FORCE_DCAST_EVENT_INT (_impl->dcast (_revent.get (), _id), ::libs::ilog_events::events::InfoLogEvent*);          \
          _levent->update_info (::libs::ilog_events::AppllPartLogInfo (_application_id, __FILE__, __LINE__), _info);                                \
          _logger->send_msg (_revent);                                                                                                              \
        }                                                                                                                                           \
    }
#endif


#ifndef EVENTS_LOG
#define EVENTS_LOG(_info)                                                                                                                        \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().events2appl_.lock ();                                                                         \
      MSG2LOGGER (_logger, _info, "uuu_events");                                                                                                 \
    }
#endif


#ifndef GUI_LOG
#define GUI_LOG(_info)                                                                                                                           \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().gui2appl_.lock ();                                                                            \
      MSG2LOGGER (_logger, _info, "uuu_gui");                                                                                                    \
    }
#endif


#ifndef DATA_LOG
#define DATA_LOG(_info)                                                                                                                          \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().data2appl_.lock ();                                                                           \
      MSG2LOGGER (_logger, _info, "uuu_data");                                                                                                   \
    }
#endif


#ifndef HTTP_LOG
#define HTTP_LOG(_info)                                                                                                                          \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().http2appl_.lock ();                                                                           \
      MSG2LOGGER (_logger, _info, "uuu_http");                                                                                                   \
    }
#endif


#ifndef APPL_LOG
#define APPL_LOG(_info)                                                                                                                          \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().appl2log_.lock ();                                                                            \
      MSG2LOGGER (_logger, _info, "uuu_main");                                                                                                   \
    }
#endif
