/**
\file       root-module-wrapers-catch-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "root-module.hpp"

namespace libs::ilink::appl::root
{
syn::IEvent::ptr
RootModule::seq_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    auto seq_ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISeqEvent > (msg);
    auto ret     = seq_ret->get_msg ();

    U3_ASSERT (ret);
    current_seq_.recv_seq_ = true;
    current_seq_.id_seq_   = seq_ret->get_seq_id ();
    return ret;
  }
  return syn::IEvent::ptr ();
}


syn::IEvent::ptr
RootModule::sync_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.sync_event_ = true;

    auto ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISyncEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }

  if (::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg))
  {
    return msg;
  }
  return syn::IEvent::ptr ();
}


syn::IEvent::ptr
RootModule::request_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.request_ = true;
    auto ret              = ::libs::iproperties::helpers::cast_event< ::libs::events::IRequestEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }
  //  инверсия, на запрос идет ответ.
  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::events::IAnswerEvent > (rmsg);
  dmsg->set_msg (msg);
  return rmsg;
}


syn::IEvent::ptr
RootModule::answer_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.answer_ = true;
    auto ret             = ::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }
  //  инверсия, пришел ответ модулю
  return msg;
}
}   // namespace libs::ilink::appl::root
