#pragma once
/**
\file       get-base-msg-helper-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_events
*/

namespace libs::events::helpers
{
/// Вспомогательная функция для "отчистки" базового сообщения от сообщений-флагов. \param[in]  msg  сообщение до отчистки. \return     базовое сообщение
inline IEvent::ptr
get_base_msg (IEvent::ptr msg)
{
  IEvent::ptr ret = msg;
  if (auto seq_msg = ::libs::iproperties::helpers::cast_event< ISeqEvent > (ret))
  {
    ret = seq_msg->get_msg ();
  }
  if (auto sync_msg = ::libs::iproperties::helpers::cast_event< ISyncEvent > (ret))
  {
    ret = sync_msg->get_msg ();
  }
  if (auto req_msg = ::libs::iproperties::helpers::cast_event< IRequestEvent > (ret))
  {
    ret = req_msg->get_msg ();
  }
  if (auto req_msg = ::libs::iproperties::helpers::cast_event< IAnswerEvent > (ret))
  {
    ret = req_msg->get_msg ();
  }

  U3_ASSERT (!::libs::iproperties::helpers::cast_event< IAnswerEvent > (ret));
  U3_ASSERT (!::libs::iproperties::helpers::cast_event< IRequestEvent > (ret));
  U3_ASSERT (!::libs::iproperties::helpers::cast_event< ISyncEvent > (ret));
  U3_ASSERT (!::libs::iproperties::helpers::cast_event< ISeqEvent > (ret));
  U3_ASSERT (ret);
  return ret;
}
}   // namespace libs::events::helpers
