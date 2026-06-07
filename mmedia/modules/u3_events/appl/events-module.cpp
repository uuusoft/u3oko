/**
\file       events-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_events
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::u3_events::appl
{
void
free_error_callback (void* parg, int code, const char* msg)
{
  EventsModule*     parent     = ::libs::helpers::casts::reinterpret_cast_helper< EventsModule* > (parg);
  const std::string error_text = std::string (msg) + ", " + std::to_string (code);
  parent->error_callback (error_text);
}


EventsModule::EventsModule ()
{
  try
  {
    text_id_module_ = ::libs::ilink::consts::id_events;
    prepare_base ();
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}


EventsModule::~EventsModule ()
{
  try
  {
    shutdown_base ();
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}


void
EventsModule::prepare_base ()
{
  auto              iappl     = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  const std::string base_path = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_event_module);
  const std::string path      = ::libs::helpers::files::make_path (base_path, std::string ("simple"));

  ::libs::helpers::files::create_folder (path);

  const std::string comp_path = ::libs::helpers::files::make_short_path (path);
  const std::string file_path = ::libs::helpers::files::make_path (comp_path, std::string ("events.db"));

  // sqlite3_config( SQLITE_CONFIG_LOG,  ::modules::u3_events::appl::free_error_callback, this );
  U3_CHECK (SQLITE_OK == sqlite3_initialize (), "sqlite3_initialize");

  if (sqlite3_open (file_path.c_str (), &pbase_))
  {
    const std::string error_text = sqlite3_errmsg (pbase_);
    sqlite3_close (pbase_);
    pbase_ = nullptr;
    U3_XLOG_ERROR ("open/create events database " + file_path + " " + error_text);
  }
  else
  {
    const std::string cmd = R"(CREATE TABLE IF NOT EXISTS EVENTS (DATE INT NOT NULL, ID_OBJECT TEXT, ID_TYPE_EVENT TEXT NOT NULL, DATA_EVENT BLOB NOT NULL))";
    ::libs::helpers::sqlite::call_exec (pbase_, cmd, "create/open events table");
  }

  U3_CHECK (pbase_, "empty pbase_");
}


void
EventsModule::shutdown_base ()
{
  if (pbase_)
  {
    sqlite3_close (pbase_);
    pbase_ = nullptr;
  }
  sqlite3_shutdown ();
}


void
EventsModule::check_process ()
{
}


void
EventsModule::error_callback (const std::string& error_text)
{
  U3_LOG_EVENTS_ERROR (std::string ("sqlite error: ") + error_text);
}

void
EventsModule::process_add_event2base (
  syn::IEvent::ptr&           msg,
  syn::AddEvent2Base::raw_ptr props)
{
  U3_LOG_EVENTS_DEV ("add event to store" + TOLOG (::libs::helpers::utils::to_string (props->get_machine_id ())) + TOLOG (props->get_object_id ()));
  try
  {
    const std::string xml_event   = ::libs::iproperties::helpers::event2xml (msg);
    auto              store_event = props->get_event ();
    auto              event       = props->get_event ();
    const auto        machine_id  = props->get_machine_id ();
    const auto        obj_id      = props->get_object_id ();
    const std::string insert_sql  = "INSERT INTO EVENTS (DATE, ID_OBJECT, ID_TYPE_EVENT, DATA_EVENT)";
    const std::string time_sql    = "";
    const std::string sql         = insert_sql +
                            " VALUES(" + ::libs::helpers::sqlite::to_sql_str (time_sql) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (obj_id) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (event->get_mid ()) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (xml_event) + ");";

    // const auto time = props->get_time ();
    //  const std::string time_sql   = "strftime('%s','now')";
    ::libs::helpers::sqlite::call_exec (pbase_, sql, "add event");
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}


void
EventsModule::process_get_data_graphs (
  syn::IEvent::ptr&                        msg,
  syn::GetDataGraphsFromEventBase::raw_ptr props)
{
  U3_LOG_EVENTS_DBG ("get data graphs from store");
  try
  {
    syn::GetDataGraphsFromEventBase::id_graphs_storage_type res;
    props->set_data_graphs (std::move (res));

#ifdef U3_FAKE_DISABLE
    std::string       xml_event;
    auto              store_event = props->get_event ();
    auto              event       = props->get_event ();
    const auto        machine_id  = props->get_machine_id ();
    const auto        obj_id      = props->get_object_id ();
    const auto        time        = props->get_time ();
    const std::string insert_sql  = "INSERT INTO EVENTS (DATE, ID_OBJECT, ID_TYPE_EVENT, DATA_EVENT)";
    const std::string time_sql    = "";
    const std::string sql         = insert_sql +
                            " VALUES(" + ::libs::helpers::sqlite::to_sql_str (time_sql) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (obj_id) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (event->get_mid ()) + ", " +
                            ::libs::helpers::sqlite::to_sql_str (xml_event) + ");";

    // const std::string time_sql   = "strftime('%s','now')";
    ::libs::helpers::sqlite::call_exec (pbase_, sql, "add event");
#endif
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}


void
EventsModule::process_update_listener (
  syn::IEvent::ptr&            msg,
  syn::UpdateListener::raw_ptr props)
{
  U3_LOG_EVENTS_DEV ("update events listener");
  try
  {
    const auto action = props->get_action ();
    if (syn::SubscribeActions::enable == action)
    {
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::enable == action");
    }
    else if (syn::SubscribeActions::disable == action)
    {
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::disable == action");
    }
    else
    {
      U3_LOG_EVENTS_ERROR ("unknown syn::SubscribeActions value");
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}
}   // namespace modules::u3_events::appl
