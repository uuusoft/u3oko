//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       benchmark-appl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    u3oko
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
//#include "benchmark-state.hpp"
#include "u3oko-appl.hpp"

namespace appls { namespace u3oko { namespace appl {

namespace bip = boost::interprocess;

U3OkoAppl::U3OkoAppl () :
  count_cycles_ (0)
{
  name_appl_      = appl::consts::name_application;
  txt_ver_        = appl::consts::txt_ver;
  ms_time_sleep_  = 5;      //особый модуль, который задействован в обработке сообщений от всех других, изменяем время ожидания следующего события в 0.
  text_id_module_ = ::libs::ilink::consts::id_bench;
}


U3OkoAppl::~U3OkoAppl ()
{}


void
U3OkoAppl::init_int (const ::libs::link::appl::InitApplication& _info)
{
  super::init_int (_info);
  return;
}


void
U3OkoAppl::init_links_int (const ::libs::link::appl::InitApplication& _info)
{
  super::init_links_int (_info);

  auto                      _main_appl = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::application::ApplicationProp> (event_props_.main_appl_);
  const RunCodeType         _type_run  = _main_appl->is_single_process () ? RunCodeType::dll : RunCodeType::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = LinkCreatorProxy::instance ();
  auto                      _iproxy    = _lproxy->impl ();

  //  Устанавливаем свойства логирования.
  links_.appl2log_->send_msg (event_props_.module_log_);
  //  Устанавливаем свойства хранилища.
  links_.appl2storage_->send_msg (event_props_.storage_module_);

  {
    XULOG_INFO ("make http link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      "uuu_appl.exe",
      "mpl_uuu_http",
      name_company_,
      name_appl_,
      "subsys_http",
      ::libs::link::details::LinkModulesType::http,
      ::libs::link::consts::size::buff_appl2http);

    IEvent::ptr _rmsg;
    auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
    _dmsg->set_start (true);

    links_.appl2http_ = _iproxy->get_connect (&_create_info);
    links_.appl2http_->send_msg (_rmsg);
  }

  UASSERT (!_main_appl->get_xml_paths ().empty ());
  if (!_main_appl->get_xml_paths ().empty ())
    {
      const auto& _xml_paths = _main_appl->get_xml_paths ();
      IEvent::ptr _rmsg;
      auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::imdata_events::events::ChangePathsDataEvent> (_rmsg);
      std::list<std::string> _xml_list(_xml_paths.begin (), _xml_paths.end ());
      _dmsg->set_paths (_xml_list);
      _dmsg->set_action (::libs::imdata_events::events::ChangePathAction::add);
      links_.appl2data_->send_msg (_rmsg);
    }
  return;
}


void
U3OkoAppl::update_catch_functs_int ()
{
  APPL_LOG ("U3OkoAppl::update_catch_functs_int");
  super::update_catch_functs_int ();

  catch_functs_[::libs::igui_events::events::CommandCodeEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _rmsg = ::libs::iproperties::helpers::cast_event<::libs::igui_events::events::CommandCodeEvent> (_msg);
        APPL_LOG ("catch ::libs::igui_events::events::CommandCodeEvent, " + _rmsg->get_code ());
        stop_module_ = true;
        return IEvent::ptr ();
      }

    return _msg;
  };

  catch_functs_[::libs::ievents::runtime::video::FrameDone::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        //APPL_LOG( "received ::libs::ievents::runtime::video::FrameDone" );
        return IEvent::ptr ();
      }

    return _msg;
  };
  return;
}


bool
U3OkoAppl::deinit_int ()
{
  if (links_.appl2http_)
    {
      IEvent::ptr _rmsg;
      auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
      _dmsg->set_start (false);
      links_.appl2http_->send_msg (_rmsg);
    }

  return super::deinit_int ();
}


::libs::ilink::appl::base::BaseModule::recv_links_type
U3OkoAppl::get_recv_link ()
{
  recv_links_type _ret;

  _ret.push_back (links_.appl2gui_);
  _ret.push_back (links_.appl2data_);
  _ret.push_back (links_.appl2http_);
  _ret.push_back (links_.appl2log_);
  _ret.push_back (links_.appl2events_);
  _ret.push_back (links_.appl2storage_);
  return _ret;
}

}}}      // namespace appls::u3oko::appl
