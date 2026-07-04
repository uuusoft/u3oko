/**
\file       benchmark-appl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3oko
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../appls-u3oko-includes_int.hpp"
#include "u3oko-appl.hpp"

namespace appls::u3oko::appl
{
U3OkoAppl::U3OkoAppl ()
{
  text_id_module_ = ::libs::ilink::consts::id_u3oko;
  ms_time_sleep_  = ::libs::link::consts::ms_wait_delay_special_msg_cycle;   //< особый модуль, который задействован в обработке сообщений от всех других, изменяем время ожидания следующего события в 0
}


void
U3OkoAppl::appl_init_int (const syn::InitApplication& info)
{
  super::appl_init_int (info);
}


void
U3OkoAppl::init_links_int (const syn::InitApplication& info)
{
  U3_XLOG_DBG ("U3OkoAppl::init_links_int::---->");
  super::init_links_int (info);

  //  Устанавливаем свойства логирования
  U3_XLOG_DBG ("U3OkoAppl::init_links_int:: pt1");
  links_.get (syn::mids::appl2log)->send_msg (appl_event_props_.module_log_, syn::CallSyncs::async, syn::Calls::set);
  //  Устанавливаем свойства хранилища
  U3_XLOG_DBG ("U3OkoAppl::init_links_int:: pt2");
  links_.get (syn::mids::appl2storage)->send_msg (appl_event_props_.storage_module_, syn::CallSyncs::async, syn::Calls::set);
  U3_XLOG_DBG ("U3OkoAppl::init_links_int::<----");
}


void
U3OkoAppl::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::CommandCodeEvent::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* rmsg = ::libs::iproperties::helpers::cast_event< syn::CommandCodeEvent > (msg);
      U3_LOG_APPL_DEV ("catch ::libs::events_gui::events::CommandCodeEvent, " + rmsg->get_code ());
      stop_module_ = true;
      return {};
    }

    return msg;
  };

  catch_funcs_[syn::FrameDone::gen_get_mid ()] =
    [] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      // U3_LOG_APPL( "received syn::FrameDone" );
      return {};
    }

    return msg;
  };
}


auto
U3OkoAppl::appl_deinit_int () -> bool
{
  return super::appl_deinit_int ();
}


auto
U3OkoAppl::get_recv_link_int () -> ::libs::ilink::appl::base::BaseModule::recv_links_type
{
  return {
#if (U3_MODULES_ENABLE_GUI == 1)
    links_.get (syn::mids::appl2gui),
#endif
    links_.get (syn::mids::appl2mdata),
    links_.get (syn::mids::appl2http),
    links_.get (syn::mids::appl2log),
    links_.get (syn::mids::appl2events),
    links_.get (syn::mids::appl2storage)
  };
}
}   // namespace appls::u3oko::appl
