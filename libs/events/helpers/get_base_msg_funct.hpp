//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_base_msg_funct.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace helpers {
/**
  \brief      Вспомогательная функция для "отчистки" базового сообщения от сообщений-флагов.
  \param[in]  _msg  сообщение до отчистки.
  \return     базовое сообщение.
  */
inline IEvent::ptr
get_base_msg (IEvent::ptr _msg)
{
  if (auto _seq_msg = ::libs::iproperties::helpers::cast_event<ISeqEvent> (_msg))
    {
      _msg = _seq_msg->get_msg ();
    }

  if (auto _sync_msg = ::libs::iproperties::helpers::cast_event<ISyncEvent> (_msg))
    {
      _msg = _sync_msg->get_msg ();
    }

  if (auto _req_msg = ::libs::iproperties::helpers::cast_event<IRequestEvent> (_msg))
    {
      _msg = _req_msg->get_msg ();
    }

  if (auto _req_msg = ::libs::iproperties::helpers::cast_event<IAnswerEvent> (_msg))
    {
      _msg = _req_msg->get_msg ();
    }

  UASSERT (!::libs::iproperties::helpers::cast_event<IAnswerEvent> (_msg));
  UASSERT (!::libs::iproperties::helpers::cast_event<IRequestEvent> (_msg));
  UASSERT (!::libs::iproperties::helpers::cast_event<ISyncEvent> (_msg));
  UASSERT (!::libs::iproperties::helpers::cast_event<ISeqEvent> (_msg));
  return _msg;
}

}}}      // namespace libs::events::helpers
