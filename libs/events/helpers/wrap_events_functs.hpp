//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       wrap_events_functs.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace helpers {
/**
\brief      Вспомогательная функция для добавления сообщению признака синхронности.
\param[in]  _msg  базовое сообщение.
\return     сообщение.
*/
inline IEvent::ptr
wrap_sync_msg (IEvent::ptr _msg)
{
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<IAnswerEvent> (_msg), "failed, try sync answer event");
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<ISyncEvent> (_msg), "failed, try sync sync event");
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<ISyncEvent> (_rmsg);
  _dmsg->set_msg (_msg);
  return _rmsg;
}
/**
\brief      Вспомогательная функция для добавлению сообщению признака запроса.
\param[in]  _msg  базовое сообщение.
\return     сообщение.
*/
inline IEvent::ptr
wrap_request_msg (IEvent::ptr _msg)
{
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<ISyncEvent> (_msg), "failed, try request sync event");
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<IAnswerEvent> (_msg), "failed, try request answer event");
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<IRequestEvent> (_msg), "failed, try request request event");
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<IRequestEvent> (_rmsg);
  _dmsg->set_msg (_msg);
  return _rmsg;
}
/**
\brief      Вспомогательная функция для добавлению сообщению признака запроса.
\param[in]  _msg  базовое сообщение.
\return     сообщение.
*/
inline IEvent::ptr
wrap_answer_msg (IEvent::ptr _msg)
{
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<ISyncEvent> (_msg), "failed, try answer sync event");
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<IAnswerEvent> (_msg), "failed, try answer answer event");
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<IRequestEvent> (_msg), "failed, try answer request event");
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<IAnswerEvent> (_rmsg);
  _dmsg->set_msg (_msg);
  return _rmsg;
}
/**
\brief      Вспомогательная функция для добавлению сообщению идентификатора последовательности.
\param[in]  _msg  базовое сообщение.
\param[in]  _id   опциональный идентификатор последовательности. Если передана пустой идентификатор, он геренируется случайным образом.
\return     сообщение.
*/
inline IEvent::ptr
wrap_seq_msg (IEvent::ptr _msg, ISeqEvent::id_type _id = ISeqEvent::id_type ())
{
  CHECK_STATE (nullptr == ::libs::iproperties::helpers::cast_event<ISeqEvent> (_msg), "failed, try seq seq event");
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<ISeqEvent> (_rmsg);
  _dmsg->set_msg (_msg);
  _dmsg->set_seq_id (_id.empty () ? ISeqEvent::id_type (boost::uuids::random_generator () ()) : _id);
  return _rmsg;
}

}}}      // namespace libs::events::helpers
