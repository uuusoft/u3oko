//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       root-module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "root-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace root {

RootModule::RootModule () :
  seqs_ ([](const StateProcessEventExt& _left, const StateProcessEventExt& _right) { return _left.id_seq_ < _right.id_seq_; }),
  deinit_stage_ (TypeStageDeInit::send_stop_msg2allmost_all),
  last_time_dump_status_system_ (boost::posix_time::microsec_clock::universal_time ())
{}


RootModule::~RootModule ()
{}


void
RootModule::init_proxys_int ()
{
  super::init_proxys_int ();
  CHECK_CALL (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "failed instance mem block allocator");
  return;
}


void
RootModule::init_links_int (const InitApplication& _info)
{
  XULOG_INFO ("uuu_soft::RootModule::init_links_int::beg, " << text_id_module_ << ":" << to_str (this));
  auto                      _main_appl = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::application::ApplicationProp> (event_props_.main_appl_.get ());
  const TypeRunCode         _type_run  = _main_appl->is_single_process () ? TypeRunCode::dll : TypeRunCode::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = LinkCreatorProxy::instance ();
  auto                      _iproxy    = _lproxy->impl ();
  auto                      _ipstorage = ::libs::iproperties::helpers::get_storage ();
  //volatile auto             _imstorage = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree();
  //_imstorage;

  //  Разделяем созданные интерфейсы между всей системой через объект "свойства".
  {
    ::libs::properties::vers::links::ILinksProperty::links_type _links;
    _links = links_;
    _ipstorage->set_prop (::libs::properties::consts::keys::links_property, std::make_shared<::libs::properties::vers::links::ILinksProperty> (_links));
  }

  {
    XULOG_INFO ("make log link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_log",
      name_company_,
      name_appl_,
      "subsys_appl2log",
      ::libs::link::details::TypeLinkModules::log,
      ::libs::link::consts::size::buff_all2log);

    links_.appl2log_ = _iproxy->get_connect (&_create_info);

    {
      IEvent::ptr _rmsg;
      auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent> (_rmsg);
      _dmsg->update_info (::libs::ilog_events::AppllPartLogInfo (name_appl_, __FILE__, __LINE__), "");
      _dmsg->set_start (true);
      links_.appl2log_->send_msg (_rmsg);
    }
    {
      IEvent::ptr _rmsg;
      auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
      _dmsg->set_start (true);
      links_.appl2log_->send_msg (_rmsg);
    }
  }

  {
    XULOG_INFO ("make events link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_events",
      name_company_,
      name_appl_,
      "subsys_events",
      ::libs::link::details::TypeLinkModules::events,
      ::libs::link::consts::size::buff_all2events);

    links_.appl2events_ = _iproxy->get_connect (&_create_info);

    IEvent::ptr _rmsg;
    auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
    _dmsg->set_start (true);
    links_.appl2events_->send_msg (_rmsg);
  }

  {
    XULOG_INFO ("make storage link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_storage",
      name_company_,
      name_appl_,
      "subsys_storage",
      ::libs::link::details::TypeLinkModules::storage,
      ::libs::link::consts::size::buff_appl2storage);

    links_.appl2storage_ = _iproxy->get_connect (&_create_info);

    IEvent::ptr _rmsg;
    auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
    _dmsg->set_start (true);
    links_.appl2storage_->send_msg (_rmsg);
  }

  {
    XULOG_INFO ("make gui link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_gui",
      name_company_,
      name_appl_,
      "subsys_gui",
      ::libs::link::details::TypeLinkModules::gui,
      ::libs::link::consts::size::buff_appl2gul);

    links_.appl2gui_ = _iproxy->get_connect (&_create_info);
  }

  {
    XULOG_INFO ("make data link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_mdata",
      name_company_,
      name_appl_,
      "subsys_data",
      ::libs::link::details::TypeLinkModules::mdata,
      ::libs::link::consts::size::buff_appl2data);

    links_.appl2data_ = _iproxy->get_connect (&_create_info);
  }

  {
    ::libs::helpers::sys::cpu::TextExtCpu _helper;
    auto                                  _info_cpu = ::libs::iproperties::helpers::cast_event<InfoCPUEvent> (event_props_.info_cpu_);
    MSG2LOGGER (links_.appl2log_, "Selected SIMD CPU : " + _helper.get_text (_info_cpu->get_type ()), name_appl_);
    MSG2LOGGER (links_.appl2log_, "Count CPU: " + to_str (_info_cpu->get_count ()), name_appl_);

    links_.appl2data_->send_msg (event_props_.info_cpu_);
  }
  XULOG_INFO ("uuu_soft::RootModule::init_links_int::end");
  return;
}


bool
RootModule::deinit_int ()
{
  XULOG_TRACE ("uuu_soft::RootModule::deinit_int::beg, " << text_id_module_ << ":0x" << to_str (this) << ", stage: " << to_str (UUU_ICAST_INT (deinit_stage_)));
  bool _ret = false;

  switch (deinit_stage_)
    {
    case TypeStageDeInit::send_stop_msg2allmost_all:
      {
        if (links_.appl2log_)
          {
            XULOG_INFO ("send stop msg 2 log");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent> (_rmsg);
            _dmsg->update_info (::libs::ilog_events::AppllPartLogInfo (name_appl_, __FILE__, __LINE__), "");
            _dmsg->set_start (false);
            links_.appl2log_->send_msg (_rmsg);
          }

        if (links_.appl2http_)
          {
            XULOG_INFO ("send stop msg 2 http");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
            _dmsg->set_start (false);
            links_.appl2http_->send_msg (_rmsg);
          }

        if (links_.appl2data_)
          {
            XULOG_INFO ("send stop msg 2 data");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
            _dmsg->set_start (false);
            links_.appl2data_->send_msg (_rmsg);
          }

        if (links_.appl2gui_)
          {
            XULOG_INFO ("send stop msg 2 gui");
            {
              IEvent::ptr _rmsg;
              auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
              _dmsg->set_start (false);
              links_.appl2gui_->send_msg (_rmsg);
            }

            {
              IEvent::ptr _rmsg;
              auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::igui_events::events::ExitApplEvent> (_rmsg);
              links_.appl2gui_->send_msg (_rmsg);
            }
          }

        if (links_.appl2events_)
          {
            XULOG_INFO ("send stop msg 2 events");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
            _dmsg->set_start (false);
            links_.appl2events_->send_msg (_rmsg);
          }

        if (links_.appl2storage_)
          {
            XULOG_INFO ("send stop msg 2 storage");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
            _dmsg->set_start (false);
            links_.appl2storage_->send_msg (_rmsg);
          }

        //std::this_thread::sleep_for ( std::chrono::milliseconds ( 3 * 1000 ) );//debug
        deinit_stage_ = TypeStageDeInit::wait_stop_data_module;
        break;
      }
    case TypeStageDeInit::wait_stop_data_module:
      {
        if (!links_.appl2data_ || !links_.appl2data_->is_connected ())
          {
            XULOG_INFO ("wait TypeStageDeInit::wait_stop_data_module done");
            links_.appl2data_.reset ();
            deinit_stage_ = TypeStageDeInit::wait_stop_gui_module;
          }
        break;
      }
    case TypeStageDeInit::wait_stop_gui_module:
      {
        if (!links_.appl2gui_ || !links_.appl2gui_->is_connected ())
          {
            XULOG_INFO ("wait TypeStageDeInit::wait_stop_gui_module done");
            links_.appl2gui_.reset ();
            deinit_stage_ = TypeStageDeInit::wait_stop_storage_module;
          }
        break;
      }
    case TypeStageDeInit::wait_stop_storage_module:
      {
        if (!links_.appl2storage_ || !links_.appl2storage_->is_connected ())
          {
            XULOG_INFO ("wait TypeStageDeInit::wait_stop_storage_module done");
            links_.appl2storage_.reset ();
            deinit_stage_ = TypeStageDeInit::wait_stop_events_module;
          }
        break;
      }
    case TypeStageDeInit::wait_stop_events_module:
      {
        if (!links_.appl2events_ || !links_.appl2events_->is_connected ())
          {
            XULOG_INFO ("wait TypeStageDeInit::wait_stop_events_module done");
            links_.appl2events_.reset ();
            deinit_stage_ = TypeStageDeInit::send_stop_msg2log_module;
          }
        break;
      }
    case TypeStageDeInit::send_stop_msg2log_module:
      {
        //std::this_thread::sleep_for (std::chrono::milliseconds (5 * 1000));
        if (links_.appl2log_)
          {
            XULOG_INFO ("begin send stop msg 2 log");
            IEvent::ptr _rmsg;
            auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
            _dmsg->set_start (false);
            links_.appl2log_->send_msg (_rmsg);
            XULOG_INFO ("end send stop msg 2 log");
          }

        deinit_stage_ = TypeStageDeInit::wait_stop_log_module;
        break;
      }
    case TypeStageDeInit::wait_stop_log_module:
      {
        if (!links_.appl2log_ || !links_.appl2log_->is_connected ())
          {
            XULOG_INFO ("wait TypeStageDeInit::send_stop_msg2log_module done");
            links_.appl2log_.reset ();
            deinit_stage_ = TypeStageDeInit::done;
          }
        break;
      }
    case TypeStageDeInit::done:
      XULOG_INFO ("wait TypeStageDeInit::done done");
      _ret = true;
      break;
    default:
      UASSERT_SIGNAL ("Unknown deinit stage");
      break;
    }

  return _ret;
}


void
RootModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_[::libs::events::ISeqEvent::gen_get_type_text_id ()] = std::bind (
    &RootModule::seq_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2);

  catch_functs_[::libs::events::ISyncEvent::gen_get_type_text_id ()] = std::bind (
    &RootModule::sync_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2);

  catch_functs_[::libs::events::IRequestEvent::gen_get_type_text_id ()] = std::bind (
    &RootModule::request_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2);

  catch_functs_[::libs::events::IAnswerEvent::gen_get_type_text_id ()] = std::bind (
    &RootModule::answer_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2);

  catch_functs_[::libs::ievents::runtime::state::ExpandTimeStatisticEvent::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        //auto _rmsg = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::state::ExpandTimeStatisticEvent> (_msg);
        auto _res = links_.appl2data_->send_msg (_msg, ::libs::link::details::TypeSyncCall::sync);
        return IEvent::ptr ();
      }
    return _msg;
  };

  return;
}


ILink::ptr
RootModule::get_dest_link (IEvent::ptr _msg)
{
  UASSERT (!current_seq_.dest_);
  //  Самые частые сообщения к основному модулю, т.к. фактически через него общаются друг с другом все другие модули.
  if (::libs::iproperties::helpers::cast_event<::libs::imdata_events::events::BaseDataEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_mdata destination");
      return links_.appl2data_;
    }
  //  Самые частые сообщения к логированию.
  if (::libs::iproperties::helpers::cast_event<::libs::ilog_events::events::BaseLogEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_log destination");
      return links_.appl2log_;
    }
  //  ???
  if (::libs::iproperties::helpers::cast_event<::libs::istorage_events::events::BaseStorageEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_storage destination, 0x" << std::hex << links_.appl2storage_.get ());
      return links_.appl2storage_;
    }
  //  ???
  if (::libs::iproperties::helpers::cast_event<::libs::igui_events::events::BaseGUIEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_gui destination");
      return links_.appl2gui_;
    }
  //  ???
  if (::libs::iproperties::helpers::cast_event<::libs::ievents_events::events::BaseEventsEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_events destination");
      return links_.appl2events_;
    }
  //  ???
  if (::libs::iproperties::helpers::cast_event<::libs::ihttp_events::events::BaseHttpEvent> (_msg))
    {
      XULOG_TRACE ("RootModule::get_dest_link, select uuu_http destination");
      return links_.appl2http_;
    }
  XULOG_TRACE ("unknown destination, " << _msg->get_mid ());
  return ILink::ptr ();
}

}}}}      // namespace libs::ilink::appl::root
