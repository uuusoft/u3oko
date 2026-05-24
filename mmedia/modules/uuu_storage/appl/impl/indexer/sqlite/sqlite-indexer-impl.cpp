/**
\file       sqlite-indexer-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       25.07.2018
\project    u3_module_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "sqlite-indexer-impl.hpp"

#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
SqliteIndexerImpl::SqliteIndexerImpl () :
  state_ (std::make_shared< StateSqliteIndexer > ()),
  state_saved_ (true),
  pbase_ (nullptr)
{
  prepare_base ();
}


SqliteIndexerImpl::~SqliteIndexerImpl ()
{
  shutdown_base ();
  save_state ();
}


void
SqliteIndexerImpl::prepare_base ()
{
  auto              iappl     = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  const std::string base_path = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_storage_module);
  // const std::string subsys_path = ::libs::helpers::files::make_path (base_path, std::string ("events"));
  const std::string path = ::libs::helpers::files::make_path (base_path, std::string ("simple"));

  ::libs::helpers::files::create_folder (path);

  const std::string comp_path = ::libs::helpers::files::make_short_path (path);
  const std::string file_path = ::libs::helpers::files::make_path (comp_path, std::string ("indexs.db"));

  // sqlite3_config( SQLITE_CONFIG_LOG,  ::modules::u3_events::appl::error_callback, this );
  U3_CHECK (SQLITE_OK == sqlite3_initialize (), "sqlite3_initialize");

  if (sqlite3_open (file_path.c_str (), &pbase_))
  {
    const std::string error_text = sqlite3_errmsg (pbase_);
    sqlite3_close (pbase_);
    pbase_ = nullptr;
    U3_XLOG_ERROR ("open/create events database path=" + file_path + " error=" + error_text);
  }
  else
  {
    const std::string cmd = "CREATE TABLE IF NOT EXISTS EVENTS (DATE INT NOT NULL, ID_OBJECT TEXT, ID_TYPE_EVENT TEXT NOT NULL, DATA_EVENT BLOB NOT NULL)";
    ::libs::helpers::sqlite::call_exec (pbase_, cmd, "create/open events table");
  }

  U3_CHECK (pbase_, "empty pbase_");
}


void
SqliteIndexerImpl::shutdown_base ()
{
  if (pbase_)
  {
    sqlite3_close (pbase_);
    pbase_ = nullptr;
  }

  sqlite3_shutdown ();
}


bool
SqliteIndexerImpl::change_state_int (const ImplRuns& state)
{
  switch (state)
  {
  case ImplRuns::run:
    load_state ();
    break;
  case ImplRuns::stop:
    save_state ();
    break;
  default:
    U3_XLOG_WARN ("unknown change state" + VTOLOG (U3_CAST_UINT32_FORCE (state)));
    return false;
  }
  return true;
}


void
SqliteIndexerImpl::set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)
{
  if (info)
  {
    info_ = *info;
  }
  update_path ();
  save_state ();   //  save probably previous state
  load_state ();
  state_saved_ = false;
}


void
SqliteIndexerImpl::update_stream_int (::libs::istorage_events::events::UpdateStream::raw_ptr info)
{
  switch (info->action_)
  {
  case ::libs::istorage_events::StreamUpdates::open:
    open_stream (info);
    break;
  case ::libs::istorage_events::StreamUpdates::close:
    close_stream (info);
    break;
  case ::libs::istorage_events::StreamUpdates::change:
    U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
    break;
  case ::libs::istorage_events::StreamUpdates::check_and_get_info:
    U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
    break;
  default:
    U3_ASSERT_SIGNAL ("find action " + to_string (info->action_));
    break;
  }

  state_saved_ = false;
}


void
SqliteIndexerImpl::get_objects_int (std::vector< ::libs::istorage_events::TypeObjectId >& objs)
{
  objs.clear ();
  objs.reserve (state_->objects_.size ());

  for (auto& obj : state_->objects_)
  {
    objs.push_back (obj.second.id_);
  }
}
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite

#endif
