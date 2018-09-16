//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       state-process-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      Файл интерфейса типа для хранения состояния обработки события внутри модуля.
*/

namespace libs { namespace link {
/**
\brief  Структура для хранения всей необходимой информации, связанной с текущим обрабатываемым событием.
*/
struct StateProcessEvent
{
  //  ext types
  using childs_type = std::list<ISeqEvent::id_type>;

  StateProcessEvent () :
    sync_ (false),
    request_ (false),
    recv_seq_ (false),
    make_seq_ (false),
    answer_ (false),
    failed_ (false)
  {}

  ~StateProcessEvent ()
  {}

  bool
  is_seq_exist () const
  {
    return id_seq_.empty () ? false : true;
  }

  bool
  is_childs_exist () const
  {
    return childs_.empty () ? false : true;
  }

  bool
  is_failed () const
  {
    return failed_;
  }

  void
  reset ()
  {
    sync_     = false;
    request_  = false;
    recv_seq_ = false;
    make_seq_ = false;
    answer_   = false;
    failed_   = false;

    msg_.reset ();
    id_seq_.reset ();
    childs_.clear ();
    error_text_.clear ();
    return;
  }

  void
  update (IEvent::ptr _msg)
  {
    msg_ = _msg;
    return;
  }

  bool               sync_;            //< Флаг синхронной передачи.
  bool               request_;         //< Флаг, наличие запроса.
  bool               answer_;          //< Флаг, наличие ответа.
  IEvent::ptr        msg_;             //< Собственно событие.
  bool               recv_seq_;        //< Флаг, событие является частью транзакции.
  bool               make_seq_;        //< Флаг, событие является частью иницированной транзакции.
  ISeqEvent::id_type id_seq_;          //< Опциональные идентификатор транзакции.
  childs_type        childs_;          //< Связанные запросы с текущим.
  bool               failed_;          //< Флаг ошибки при обработки запроса.
  std::string        error_text_;      //< Опциональная строка с сообщение об ошибке.
};
/**
\brief  ???
*/
inline std::string
to_str (const StateProcessEvent& _val)
{
  std::string _res;
  _res += std::string ("StateProcessEvent[") + "sync=" + ::to_str (_val.sync_) + "request=" + ::to_str (_val.request_) + "answer=" + ::to_str (_val.answer_) + "msg=" + _val.msg_->get_mid () + "]";
  return _res;
}

}}      // namespace libs::link
