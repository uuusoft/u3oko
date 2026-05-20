#pragma once
/**
\file       wrap-events-helper-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_events
*/

namespace libs::events::helpers
{
/// Вспомогательная функция для добавления сообщению признака синхронности
/// \param[in]  msg  базовое сообщение
/// \return     сообщение
inline IEvent::ptr
wrap_sync_msg (IEvent::ptr msg)
{
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< IAnswerEvent > (msg), "try sync answer event");
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< ISyncEvent > (msg), "try sync sync event");
  IEvent::ptr rmsg;
  ::libs::iproperties::helpers::create_event< ISyncEvent > (rmsg)->set_msg (msg);
  return rmsg;
}

/// Вспомогательная функция для добавлению сообщению признака запроса
/// \param[in]  msg  базовое сообщение
/// \return     сообщение
inline IEvent::ptr
wrap_request_msg (IEvent::ptr msg)
{
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< ISyncEvent > (msg), "try request sync event");
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< IAnswerEvent > (msg), "try request answer event");
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< IRequestEvent > (msg), "try request request event");
  IEvent::ptr rmsg;
  ::libs::iproperties::helpers::create_event< IRequestEvent > (rmsg)->set_msg (msg);
  return rmsg;
}

/// Вспомогательная функция для добавлению сообщению признака запроса
/// \param[in]  msg  базовое сообщение
/// \return     сообщение
inline IEvent::ptr
wrap_answer_msg (IEvent::ptr msg)
{
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< ISyncEvent > (msg), "try answer sync event");
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< IAnswerEvent > (msg), "try answer answer event");
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< IRequestEvent > (msg), "try answer request event");
  IEvent::ptr rmsg;
  ::libs::iproperties::helpers::create_event< IAnswerEvent > (rmsg)->set_msg (msg);
  return rmsg;
}

/// Вспомогательная функция для добавлению сообщению идентификатора последовательности
/// \param[in]  msg  базовое сообщение
/// \param[in]  id   опциональный идентификатор последовательности. Если передана пустой идентификатор, он геренируется случайным образом
/// \return     сообщение
inline IEvent::ptr
wrap_seq_msg (IEvent::ptr msg, ISeqEvent::id_type id = ISeqEvent::id_type ())
{
  U3_CHECK (nullptr == ::libs::iproperties::helpers::cast_event< ISeqEvent > (msg), "try seq seq event");
  IEvent::ptr rmsg;
  auto        dmsg = ::libs::iproperties::helpers::create_event< ISeqEvent > (rmsg);
  dmsg->set_msg (msg);
  dmsg->set_seq_id (id.empty () ? ISeqEvent::id_type (boost::uuids::random_generator () ()) : id);
  return rmsg;
}
}   // namespace libs::events::helpers
