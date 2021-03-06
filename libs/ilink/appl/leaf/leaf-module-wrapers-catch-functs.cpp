//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       leaf-module-wrapers-catch-functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "leaf-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace leaf {

IEvent::ptr
LeafModule::seq_msg_catch_funct (IEvent::ptr _msg, bool _forward)
{
  if (_forward)
    {
      auto _seq_ret = ::libs::iproperties::helpers::cast_event<::libs::events::ISeqEvent> (_msg);
      auto _ret     = _seq_ret->get_msg ();

      UASSERT (_ret);
      UASSERT (!_seq_ret->get_seq_id ().empty ());

      current_seq_.recv_seq_ = true;
      current_seq_.id_seq_   = _seq_ret->get_seq_id ();
      return _ret;
    }

  UASSERT (current_seq_.request_);      //  это должен быть запрос, иначе быссмысленно.
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::events::ISeqEvent> (_rmsg);
  //  для конечного модуля, если пришло сообщение  с идентификатором, используем его для ответа. И изначальное сообщение должно быть запросом.
  _dmsg->set_msg (_msg);
  _dmsg->set_seq_id (current_seq_.id_seq_);
  return _rmsg;
}


IEvent::ptr
LeafModule::sync_msg_catch_funct (IEvent::ptr _msg, bool _forward)
{
  if (_forward)
    {
      auto _ret = ::libs::iproperties::helpers::cast_event<::libs::events::ISyncEvent> (_msg)->get_msg ();
      UASSERT (_ret);
      return _ret;
    }
  if (::libs::iproperties::helpers::cast_event<::libs::events::IAnswerEvent> (_msg))
    {
      return _msg;
    }
  return IEvent::ptr ();
}


IEvent::ptr
LeafModule::request_msg_catch_funct (IEvent::ptr _msg, bool _forward)
{
  if (_forward)
    {
      current_seq_.request_ = true;
      auto _ret             = ::libs::iproperties::helpers::cast_event<::libs::events::IRequestEvent> (_msg)->get_msg ();
      UASSERT (_ret);
      return _ret;
    }
  //  инверсия, на запрос идет ответ.
  XULOG_TRACE ("LeafModule::request_msg_catch_funct, msg=" << _msg->get_mid () << ", as answer");
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::events::IAnswerEvent> (_rmsg);
  _dmsg->set_msg (_msg);
  return _rmsg;
}


IEvent::ptr
LeafModule::answer_msg_catch_funct (IEvent::ptr _msg, bool _forward)
{
  if (_forward)
    {
      current_seq_.answer_ = true;
      auto _ret            = ::libs::iproperties::helpers::cast_event<::libs::events::IAnswerEvent> (_msg)->get_msg ();
      UASSERT (_ret);
      return _ret;
    }
  //  инверсия, пришел ответ модулю
  return _msg;
}

}}}}      // namespace libs::ilink::appl::leaf
