#pragma once
/**
\file       get-base-msg-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::events::helpers
{
/// Вспомогательная функция для "отчистки" базового сообщения от сообщений-флагов
/// \param[in]  msg  сообщение до отчистки
/// \return     базовое сообщение
inline IEvent::ptr
get_base_msg (IEvent::ptr msg)
{
  IEvent::ptr ret = msg;
  if (auto* seq_msg = ::libs::iproperties::helpers::cast_event< ISeqEvent > (ret))
  {
    ret = seq_msg->get_msg ();
  }
  if (auto* sync_msg = ::libs::iproperties::helpers::cast_event< ISyncEvent > (ret))
  {
    ret = sync_msg->get_msg ();
  }
  if (auto* req_msg = ::libs::iproperties::helpers::cast_event< IRequestEvent > (ret))
  {
    ret = req_msg->get_msg ();
  }
  if (auto* req_msg = ::libs::iproperties::helpers::cast_event< IAnswerEvent > (ret))
  {
    ret = req_msg->get_msg ();
  }

  ::libs::utility::checks::throw_ifn (!::libs::iproperties::helpers::cast_event< IAnswerEvent > (ret));
  ::libs::utility::checks::throw_ifn (!::libs::iproperties::helpers::cast_event< IRequestEvent > (ret));
  ::libs::utility::checks::throw_ifn (!::libs::iproperties::helpers::cast_event< ISyncEvent > (ret));
  ::libs::utility::checks::throw_ifn (!::libs::iproperties::helpers::cast_event< ISeqEvent > (ret));
  ::libs::utility::checks::throw_ifn ((bool) ret);
  return ret;
}
}   // namespace libs::events::helpers
