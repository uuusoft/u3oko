/**
\file       benchmark-appl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3oko
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
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
  super::init_links_int (info);

  //  Устанавливаем свойства логирования.
  links_.get (syn::mids::appl2log)->send_msg (appl_event_props_.module_log_, syn::CallSyncs::async, syn::Calls::set);
  //  Устанавливаем свойства хранилища.
  links_.get (syn::mids::appl2storage)->send_msg (appl_event_props_.storage_module_, syn::CallSyncs::async, syn::Calls::set);
}


void
U3OkoAppl::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::CommandCodeEvent::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto rmsg = ::libs::iproperties::helpers::cast_event< syn::CommandCodeEvent > (msg);
      U3_LOG_APPL_DEV ("catch ::libs::igui_events::events::CommandCodeEvent, " + rmsg->get_code ());
      stop_module_ = true;
      return ::libs::events::IEvent::ptr ();
    }

    return msg;
  };

  catch_funcs_[syn::FrameDone::gen_get_mid ()] =
    [] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      // U3_LOG_APPL( "received syn::FrameDone" );
      return ::libs::events::IEvent::ptr ();
    }

    return msg;
  };
}


bool
U3OkoAppl::appl_deinit_int ()
{
  return super::appl_deinit_int ();
}


::libs::ilink::appl::base::BaseModule::recv_links_type
U3OkoAppl::get_recv_link ()
{
  return recv_links_type {
#ifdef U3_GUI_ENABLE
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
