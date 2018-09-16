#pragma once
/**
\file       defines_log_except.hpp
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      Отладочные и вспогательные функции
*/
#if defined(UUU_DISABLED_EVENTS_MACROS)

#ifndef EXCEPT_LOG
#define EXCEPT_LOG(_logger, x) \
  UASSERT_SIGNAL ("failed");   \
  x;
#endif

#ifndef APPL_EXCEPT_LOG
#define APPL_EXCEPT_LOG(_logger, _info)
#endif

#ifndef EVENTS_EXCEPT_LOG
#define EVENTS_EXCEPT_LOG(_info)
#endif

#ifndef GUI_EXCEPT_LOG
#define GUI_EXCEPT_LOG(_info)
#endif

#ifndef DATA_EXCEPT_LOG
#define DATA_EXCEPT_LOG(_info)
#endif

#ifndef HTTP_EXCEPT_LOG
#define HTTP_EXCEPT_LOG(_info)
#endif

#else


#ifndef EXCEPT_LOG
#define EXCEPT_LOG(_logger, _info, _application_id)                                                                                                 \
  XULOG_ERROR (_application_id << std::string ("::uuu_exception, ") << _info);                                                                      \
  if (_logger)                                                                                                                                      \
    {                                                                                                                                               \
      auto _demons = ::libs::iproperties::helpers::cast_prop_demons (); \
      auto _events = _demons->get_events_lockfree ();                                                                                               \
      if (_events)                                                                                                                                  \
        {                                                                                                                                           \
          auto       _impl   = _events->impl ();                                                                                                    \
          const auto _id     = ::libs::ilog_events::events::ExceptLogEvent::gen_get_mid ();                                                \
          auto       _revent = _impl->get (_id);                                                                                                    \
          auto       _levent = UUU_FORCE_DCAST_EVENT_INT (_impl->dcast (_revent.get (), _id), ::libs::ilog_events::events::ExceptLogEvent*);        \
          _levent->update_info (::libs::ilog_events::AppllPartLogInfo (_application_id, __FILE__, __LINE__), "exception: " + std::string (_info));  \
          _logger->send_msg (_revent);                                                                                                              \
        }                                                                                                                                           \
    }
#endif


#ifndef APPL_EXCEPT_LOG
#define APPL_EXCEPT_LOG(_logger, _info) EXCEPT_LOG (_logger, _info, appl::consts::name_application);
#endif


#ifndef EVENTS_EXCEPT_LOG
#define EVENTS_EXCEPT_LOG(_info)                                                                                                                 \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().events2appl_.lock ();                                                                         \
      EXCEPT_LOG (_logger, _info, "uuu_events");                                                                                                 \
    }
#endif


#ifndef GUI_EXCEPT_LOG
#define GUI_EXCEPT_LOG(_info)                                                                                                                    \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().gui2appl_.lock ();                                                                            \
      EXCEPT_LOG (_logger, _info, "uuu_gui");                                                                                                    \
    }
#endif


#ifndef DATA_EXCEPT_LOG
#define DATA_EXCEPT_LOG(_info)                                                                                                                   \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().data2appl_.lock ();                                                                           \
      EXCEPT_LOG (_logger, _info, "uuu_data");                                                                                                   \
    }
#endif


#ifndef HTTP_EXCEPT_LOG
#define HTTP_EXCEPT_LOG(_info)                                                                                                                   \
  if (::libs::iproperties::helpers::get_prop_links ())                                                                                           \
    {                                                                                                                                            \
      auto _links  = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ()); \
      auto _logger = _links->get_links_lockfree ().http2appl_.lock ();                                                                           \
      EXCEPT_LOG (_logger, _info, "uuu_http");                                                                                                   \
    }
#endif

#endif
