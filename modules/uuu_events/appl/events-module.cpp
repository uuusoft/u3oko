//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       events-module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
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
/**
\brief  
*/
void
error_callback (void* _parg, int _code, const char* _msg)
{
  EventsModule*     _parent     = UUU_MEM_CAST<EventsModule*> (_parg);
  const std::string _error_text = std::string (_msg) + ", " + to_str (_code);
  _parent->error_callback (_error_text);
  return;
}


EventsModule::EventsModule () :
  pbase_ (nullptr)
{
  XULOG_TEST ("EventsModule::EventsModule, beg");
  auto              _iappl       = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();
  const std::string _base_path   = _iappl->get_path (::libs::iproperties::appl_paths::TypePath::work);
  const std::string _subsys_path = ::libs::helpers::files::make_path (_base_path, std::string ("events"));
  const std::string _path        = ::libs::helpers::files::make_path (_subsys_path, std::string ("simple"));

  ::libs::helpers::files::create_folder (_path);

  const std::string _comp_path = ::libs::helpers::files::make_short_path (_path);
  const std::string _file_path = ::libs::helpers::files::make_path (_comp_path, std::string ("events.db"));

  //sqlite3_config( SQLITE_CONFIG_LOG,  ::modules::uuu_events::appl::error_callback, this );
  CHECK_CALL (SQLITE_OK == sqlite3_initialize (), "failed sqlite3_initialize");
  //UASSERT( sqlite3_threadsafe() );

  XULOG_TEST ("EventsModule::EventsModule, prepare open events database");
  if (sqlite3_open (_file_path.c_str (), &pbase_))
    {
      const std::string _error_text = sqlite3_errmsg (pbase_);
      sqlite3_close (pbase_);
      pbase_ = nullptr;
      XULOG_ERROR ("failed open/create events database, " << _file_path + ", " << _error_text);
    }
  else
    {
      const std::string _cmd = "CREATE TABLE IF NOT EXISTS EVENTS (DATE INT NOT NULL, ID_OBJECT TEXT, ID_TYPE_EVENT TEXT NOT NULL, DATA_EVENT BLOB NOT NULL)";
      call_exec (pbase_, _cmd, "create/open events table");
    }

  CHECK_STATE (pbase_, "empty pbase_");
  text_id_module_ = ::libs::ilink::consts::id_events;
  XULOG_TEST ("EventsModule::EventsModule, end");
}


EventsModule::~EventsModule ()
{
  if (pbase_)
    {
      sqlite3_close (pbase_);
      pbase_ = nullptr;
    }

  sqlite3_shutdown ();
}


void
EventsModule::init_int (const ::libs::link::appl::InitApplication& _info)
{
  super::init_int (_info);
  name_company_ = _info.name_company_;
  name_appl_    = _info.name_appl_;
  check_process ();
  return;
}


void
EventsModule::init_proxys_int ()
{
  super::init_proxys_int ();
  CHECK_CALL (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "failed, create block mem allocator");
  return;
}


::libs::ilink::appl::base::BaseModule::recv_links_type
EventsModule::get_recv_link ()
{
  recv_links_type _ret;
  _ret.push_back (links_.events2appl_);
  return _ret;
}


bool
EventsModule::catch_event (IEvent::ptr _evnt)
{
  //_recv_msg = true;
  if (auto _pevnt = ::libs::iproperties::helpers::cast_event<revents::video::DetectViolation> (_evnt))
    {
      //EVENTS_LOG( "test recv violation " );
    }
  return true;
}


bool
EventsModule::is_now_sleep_thread (bool _now_recv_evnt)
{
  return _now_recv_evnt ? false : true;
}


bool
EventsModule::deinit_int ()
{
  XULOG_INFO ("EventsModule::deinit_int: beg");
  {
    auto _links = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    _links->update_links_lockfree ().events2appl_.reset ();
  }

  links_.events2appl_->destroy ();
  links_.events2appl_.reset ();
  XULOG_INFO ("EventsModule::deinit_int: end");
  return true;
}


void
EventsModule::check_process ()
{
  return;
}


void
EventsModule::init_links_int (const ::libs::link::appl::InitApplication& _info)
{
  const std::string         _name_data = "";
  RunCodeType               _type_run  = RunCodeType::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = LinkCreatorProxy::instance ();
  volatile auto             _ipstorage = ::libs::iproperties::helpers::get_storage ();

  _ipstorage;

  {
    ::libs::link::CreateInfo _create_info (
      _type_run,
      _name_data,
      "mpl_uuu_events",
      _info.name_company_,
      _info.name_appl_,
      "subsys_events",
      ::libs::link::details::LinkModulesType::events,
      ::libs::link::consts::size::buff_all2events);

    links_.events2appl_ = _lproxy->impl ()->get_listen (&_create_info);
  }

  ///пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ.
  {
    auto  _proplinks = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& _links     = _proplinks->update_links_lockfree ();

    _links.events2appl_ = links_.events2appl_;
    logger_             = links_.events2appl_;
  }
  return;
}


void
EventsModule::error_callback (const std::string& _error_text)
{
  EVENTS_LOG (std::string ("sqlite error: ") + _error_text);
  return;
}

}}}      // namespace modules::uuu_events::appl
