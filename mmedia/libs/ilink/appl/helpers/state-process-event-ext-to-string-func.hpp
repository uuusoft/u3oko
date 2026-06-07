#pragma once
/**
\file       state-process-event-ext-to-string-func.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

// old shit
namespace libs::ilink::appl::helpers
{
#ifdef U3_FAKE_DISABLE
inline std::string
to_string (const StateProcessEventExt& obj)
{
  std::string ret;

  ret += "sync " + std::to_string (obj.sync_event_);
  ret += ", request_ " + std::to_string (obj.request_);
  ret += ", answer_ " + std::to_string (obj.answer_);
  ret += ", recv_seq_ " + std::to_string (obj.recv_seq_);
  ret += ", make_seq_ " + std::to_string (obj.make_seq_);

  if (obj.make_seq_ || obj.recv_seq_)
  {
    ret += ", id " + obj.id_seq_.name ();
  }

  ret += ", msg " + (obj.msg_ ? obj.msg_->get_mid () : "empty");
  return ret;
}
#endif
}   // namespace libs::ilink::appl::helpers
