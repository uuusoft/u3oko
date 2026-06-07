/**
\file       leaf-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
::libs::events::IEvent::ptr
LeafModule::seq_msg_catch_func (
  ::libs::events::IEvent::ptr& msg,
  bool                         forward,
  const StateProcessEventExt&  process_state)
{
  try
  {
    if (forward)
    {
      auto seq_ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISeqEvent > (msg);
      auto ret     = seq_ret->get_msg ();

      U3_ASSERT (ret);
      U3_ASSERT (!seq_ret->get_seq_id ().empty ());

      current_seq_.recv_seq_ = true;
      current_seq_.id_seq_   = seq_ret->get_seq_id ();
      return ret;
    }

    U3_ASSERT (current_seq_.request_);   //  это должен быть запрос, иначе быссмысленно.
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::events::ISeqEvent > (rmsg);
    //  для конечного модуля, если пришло сообщение  с идентификатором, используем его для ответа. И изначальное сообщение должно быть запросом.
    dmsg->set_msg (msg);
    dmsg->set_seq_id (current_seq_.id_seq_);
    return rmsg;
  }
  catch (const std::exception& e)
  {
    U3_LOG_APPL_EXCEPT (e.what ());
  }
  return ::libs::events::IEvent::ptr ();
}


::libs::events::IEvent::ptr
LeafModule::sync_msg_catch_func (
  ::libs::events::IEvent::ptr& msg,
  bool                         forward,
  const StateProcessEventExt&  process_state)
{
  try
  {
    if (forward)
    {
      auto ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISyncEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }
    if (::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg))
    {
      return msg;
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_APPL_EXCEPT (e.what ());
  }
  return ::libs::events::IEvent::ptr ();
}


::libs::events::IEvent::ptr
LeafModule::request_msg_catch_func (
  ::libs::events::IEvent::ptr& msg,
  bool                         forward,
  const StateProcessEventExt&  process_state)
{
  try
  {
    if (forward)
    {
      current_seq_.request_ = true;
      auto ret              = ::libs::iproperties::helpers::cast_event< ::libs::events::IRequestEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }

    //  инверсия, на запрос идет ответ.
    ::libs::events::IEvent::ptr rmsg;
    auto                        dmsg = ::libs::iproperties::helpers::create_event< ::libs::events::IAnswerEvent > (rmsg);

    dmsg->set_msg (msg);
    return rmsg;
  }
  catch (const std::exception& e)
  {
    U3_LOG_APPL_EXCEPT (e.what ());
  }
  return ::libs::events::IEvent::ptr ();
}


::libs::events::IEvent::ptr
LeafModule::answer_msg_catch_func (
  ::libs::events::IEvent::ptr& msg,
  bool                         forward,
  const StateProcessEventExt&  process_state)
{
  try
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
  catch (const std::exception& e)
  {
    U3_LOG_APPL_EXCEPT (e.what ());
  }
  return ::libs::events::IEvent::ptr ();
}


::libs::events::IEvent::ptr
LeafModule::default_catch_func (::libs::events::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state)
{
  return ::libs::events::IEvent::ptr ();
}
}   // namespace libs::ilink::appl::leaf
