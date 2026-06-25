/**
\file       events-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
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
  U3_XLOG_DBG ("EventsModule::EventsModule::---->");
  text_id_module_ = ::libs::ilink::consts::id_events;
  // dbg_event_cycle_ = true;
}


EventsModule::~EventsModule ()
{
  try
  {
    shutdown_base ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::prepare_base ()
{
  U3_XLOG_DBG ("EventsModule::prepare_base::---->");
  auto*      osprops   = ::libs::iproperties::helpers::get_shared_prop_os ();
  auto       iappl     = osprops->get_paths_lockfree ();
  const auto base_path = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_event_module);
  const auto path      = ::libs::helpers::files::make_path (base_path, std::string ("simple"));

  ::libs::helpers::files::create_folder (path);

  const std::string comp_path    = ::libs::helpers::files::make_short_path (path);
  const std::string file_path    = ::libs::helpers::files::make_path (comp_path, std::string ("events.db"));
  auto              new_database = false;

  try
  {
    const auto header = SQLite::Database::getHeaderInfo (file_path);

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    std::cout << "Magic header string: " << header.headerStr << std::endl;
    std::cout << "Page size bytes: " << header.pageSizeBytes << std::endl;
    std::cout << "File format write version: " << (int) header.fileFormatWriteVersion << std::endl;
    std::cout << "File format read version: " << (int) header.fileFormatReadVersion << std::endl;
    std::cout << "Reserved space bytes: " << (int) header.reservedSpaceBytes << std::endl;
    std::cout << "Max embedded payload fraction " << (int) header.maxEmbeddedPayloadFrac << std::endl;
    std::cout << "Min embedded payload fraction: " << (int) header.minEmbeddedPayloadFrac << std::endl;
    std::cout << "Leaf payload fraction: " << (int) header.leafPayloadFrac << std::endl;
    std::cout << "File change counter: " << header.fileChangeCounter << std::endl;
    std::cout << "Database size pages: " << header.databaseSizePages << std::endl;
    std::cout << "First freelist trunk page: " << header.firstFreelistTrunkPage << std::endl;
    std::cout << "Total freelist trunk pages: " << header.totalFreelistPages << std::endl;
    std::cout << "Schema cookie: " << header.schemaCookie << std::endl;
    std::cout << "Schema format number: " << header.schemaFormatNumber << std::endl;
    std::cout << "Default page cache size bytes: " << header.defaultPageCacheSizeBytes << std::endl;
    std::cout << "Largest B tree page number: " << header.largestBTreePageNumber << std::endl;
    std::cout << "Database text encoding: " << header.databaseTextEncoding << std::endl;
    std::cout << "User version: " << header.userVersion << std::endl;
    std::cout << "Incremental vaccum mode: " << header.incrementalVaccumMode << std::endl;
    std::cout << "Application ID: " << header.applicationId << std::endl;
    std::cout << "Version valid for: " << header.versionValidFor << std::endl;
    std::cout << "SQLite version: " << header.sqliteVersion << std::endl;
#endif
  }
  catch (std::exception& excpt)
  {
    U3_LOG_EVENTS_MARK ("create new database" + TOLOG (file_path) + TOLOG (std::string (excpt.what ())))
    new_database = true;
  }

  if (new_database)
  {
    base_ = std::make_unique< SQLite::Database > (file_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    const std::string cmd = R"(CREATE TABLE IF NOT EXISTS EVENTS (DATE INT NOT NULL, ID_OBJECT TEXT, ID_TYPE_EVENT TEXT NOT NULL, DATA_EVENT BLOB NOT NULL))";
    ::libs::helpers::sqlite::call_exec (base_->getHandle (), cmd, "create/open events table");
  }
  else
  {
    if (!SQLite::Database::isUnencrypted (file_path))
    {
      U3_LOG_EVENTS_MARK ("dababase uncrypted" + TOLOG (file_path));
    }

    base_ = std::make_unique< SQLite::Database > (file_path, SQLite::OPEN_READWRITE);
  }
}


void
EventsModule::shutdown_base ()
{
  base_.reset ();
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
EventsModule::process_change_state_process (
  syn::IEvent::ptr&                     msg,
  syn::ChangeStateProcessEvent::raw_ptr props)
{
  try
  {
    if (!props->is_start ())
    {
      U3_LOG_EVENTS_INFO ("stop events module");
      stop_module_ = true;
      return;
    }
    U3_LOG_EVENTS_INFO ("start events module");
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::process_add_event2base (
  syn::IEvent::ptr&           msg,
  syn::AddEvent2Base::raw_ptr props)
{
  U3_LOG_EVENTS_DEV ("add event to store machind_id=" + ::libs::helpers::utils::to_string (props->get_machine_id ()) + TOLOG (props->get_object_id ()));
  try
  {
    if (size_controller_.compression_requared (base_.get ()))
    {
      U3_LOG_EVENTS_MARK ("compress database");
    }

    // const std::string event_body = ::libs::iproperties::helpers::event2json (msg);
    // const std::string event_body   = ::libs::iproperties::helpers::event2xml (msg);
    const std::string event_body  = msg->save_json ();
    auto              store_event = props->get_event ();
    auto              event       = props->get_event ();
    const auto        machine_id  = props->get_machine_id ();
    const auto        obj_id      = props->get_object_id ();
    const std::string time_sql    = "";
    U3_LOG_EVENTS_DEV (FTOLOG (event_body));

    const std::string sql =
      "INSERT INTO EVENTS (DATE, ID_OBJECT, ID_TYPE_EVENT, DATA_EVENT) VALUES(" +
      ::libs::helpers::sqlite::to_sql_str (time_sql) + ", " +
      ::libs::helpers::sqlite::to_sql_str (obj_id) + ", " +
      ::libs::helpers::sqlite::to_sql_str (event->get_mid ()) + ", " +
      ::libs::helpers::sqlite::to_sql_str (event_body) +
      ");";

#if 1
    ::libs::helpers::sqlite::call_exec (base_->getHandle (), sql, "add event");
#else
    // const auto time = props->get_time ();
    //  const std::string time_sql   = "strftime('%s','now')";
    ::libs::helpers::sqlite::call_exec (pbase_, sql, "add event");
#endif
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::process_get_data_graphs (
  syn::IEvent::ptr&                        msg,
  syn::GetDataGraphsFromEventBase::raw_ptr props)
{
  U3_LOG_EVENTS_DBG ("EventsModule::process_get_data_graphs::->");
  try
  {
    syn::GetDataGraphsFromEventBase::id_graphs_storage_type res;
    props->set_data_graphs (std::move (res));

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::process_update_listener (
  syn::IEvent::ptr&            msg,
  syn::UpdateListener::raw_ptr props)
{
  U3_LOG_EVENTS_DBG ("EventsModule::process_update_listener::->");
  try
  {
    switch (props->get_action ())
    {
    case syn::SubscribeActions::enable:
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::enable == action");
      break;
    case syn::SubscribeActions::disable:
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::disable == action");
      break;
    default:
      U3_LOG_EVENTS_ERROR ("unknown syn::SubscribeActions value");
      break;
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::process_get_events_from_base (
  syn::IEvent::ptr&               msg,
  syn::GetEventsFromBase::raw_ptr props)
{
  U3_LOG_EVENTS_DBG ("EventsModule::process_get_events_from_base::->" + TOLOG (::boost::json::serialize (props->get_request ())));
  auto       jsn = props->get_request ().as_object ();
  const auto sql = ::libs::helpers::json::get_string (jsn["sql"]);
  // const auto sql  = "SELECT name FROM sqlite_schema WHERE type ='table' AND name NOT LIKE 'sqlite_%'";
  U3_LOG_EVENTS_DEV (TOLOG (sql));
  // U3_LOG_EVENTS_DEV (TOLOG (sql2));

  try
  {
    std::vector< syn::IEvent::ptr > events;
    events.reserve (consts::max_return_count_events);

    std::int32_t      step_counter = 0;
    SQLite::Statement query (*base_, sql);
    while (query.executeStep ())
    {
      //    const std::string cmd = R"(CREATE TABLE IF NOT EXISTS EVENTS (DATE INT NOT NULL, ID_OBJECT TEXT, ID_TYPE_EVENT TEXT NOT NULL, DATA_EVENT BLOB NOT NULL))";
      const auto date       = query.getColumn (0).getInt ();
      const auto obj_id     = query.getColumn (1).getString ();
      const auto event_id   = query.getColumn (2).getString ();
      const auto event_data = query.getColumn (3).getBlob ();
      U3_LOG_EVENTS_DEV (VTOLOG (step_counter) + VTOLOG (date) + TOLOG (obj_id) + TOLOG (event_id));
      // std::cout << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << "\")\n";
      // events.emplace_back( helpers:: );
      if (++step_counter >= consts::max_return_count_events)
      {
        break;
      }

      props->set_events (events);
    }

    // const std::string xml_event   = ::libs::iproperties::helpers::event2xml (msg);
    // auto              store_event = props->get_event ();
    // auto              event       = props->get_event ();
    // const auto        machine_id  = props->get_machine_id ();
    // const auto        obj_id      = props->get_object_id ();
    // const std::string insert_sql  = "INSERT INTO EVENTS (DATE, ID_OBJECT, ID_TYPE_EVENT, DATA_EVENT)";
    // const std::string time_sql    = "";
    // const std::string sql         = insert_sql +
    //                       " VALUES(" + ::libs::helpers::sqlite::to_sql_str (time_sql) + ", " +
    //                     ::libs::helpers::sqlite::to_sql_str (obj_id) + ", " +
    //                   ::libs::helpers::sqlite::to_sql_str (event->get_mid ()) + ", " +
    //                 ::libs::helpers::sqlite::to_sql_str (xml_event) + ");";

    // const auto time = props->get_time ();
    //  const std::string time_sql   = "strftime('%s','now')";
    //::libs::helpers::sqlite::call_exec (pbase_, sql, "get events");
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }


#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  void sync_event_props (
    const time_period_type&       time_period,
    const id_graphs_storage_type& data_graph_ids,
    const hids_storage_type&      event_types,
    const events_res_type&        events_from_database,
    const std::string&            sql_request);

  void                          set_data_graphs (id_graphs_storage_type & events);
  const id_graphs_storage_type& get_data_graphs () const;
  void                          set_events (events_res_type & events);
  const events_res_type&        get_events () const;
  void                          set_types (hids_storage_type & types);
  const hids_storage_type&      get_types () const;
  void                          set_request (std::string&);
  const std::string&            get_request () const;
#endif
}
}   // namespace modules::mevents::appl
