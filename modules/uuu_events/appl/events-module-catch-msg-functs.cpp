//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       events-module-catch-msg-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.09.2018
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "consts/vals.hpp"
#include "syn_types.hpp"
#include "events-module.hpp"

namespace modules { namespace uuu_events { namespace appl {

void
EventsModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_[ChangStateProcessTypeEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<ChangStateProcessTypeEvent> (_msg);
        UASSERT (_props);
        process_change_state_process (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[WrapperEventsEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _wrap_msg = ::libs::iproperties::helpers::cast_event<WrapperEventsEvent> (_msg);
        return _wrap_msg->get_msg ();
      }
    return _msg;
  };

  catch_functs_[AddEvent2Base::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<AddEvent2Base> (_msg);
        UASSERT (_props);
        process_add_event2base (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };
  return;
}


void
EventsModule::process_change_state_process (ChangStateProcessTypeEvent::raw_ptr _props)
{
  if (!_props->is_start ())
    {
      EVENTS_LOG ("Stop events module");
      stop_module_ = true;
      return;
    }
  EVENTS_LOG ("Start events module");
  return;
}


void
EventsModule::process_add_event2base (AddEvent2Base::raw_ptr _props)
{
  auto _store_event = _props->get_event ();
  XULOG_TEST ("catch " << _store_event->get_mid ());

  auto              _event = _props->get_event ();
  std::string       _xml_event;
  const std::string _insert_sql = "INSERT INTO EVENTS (DATE, ID_OBJECT, ID_TYPE_EVENT, DATA_EVENT)";
  //const std::string _time_sql   = "strftime('%s','now')";
  const std::string _time_sql   = "";
  const std::string _sql        = _insert_sql + " VALUES(" + to_sql_str (_time_sql) + ", " + to_sql_str (_props->get_object_id ()) + ", " + to_sql_str (_event->get_mid ()) + ", " + to_sql_str (_xml_event) + ");";

  call_exec (pbase_, _sql, "add event");
  return;
}

}}}      // namespace modules::uuu_events::appl
