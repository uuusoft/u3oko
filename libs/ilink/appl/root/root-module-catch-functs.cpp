//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       root-module-catch-functs.cpp
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
#include "root-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace root {

IEvent::ptr
RootModule::default_catch_funct (IEvent::ptr _msg, bool _forward)
{
  if (_forward)
    {
      XULOG_TRACE ("RootModule::default_catch_funct, " << text_id_module_ << ", " << _msg->get_mid ())
      //  если сообщение уже пришло с транзакцией, значит это ответ на нашу транзакцию.
      if (current_seq_.recv_seq_)
        {
          UASSERT (current_seq_.answer_);
          return IEvent::ptr ();
        }
      UASSERT (!current_seq_.dest_);
      //  Ищем модуль будет обрабатывать данное сообщение и, если модуль существует, помечаем сообщение для транзакции.
      current_seq_.dest_ = get_dest_link (_msg);
      //  инициируем новую транзакцию.
      if (current_seq_.dest_ && (current_seq_.sync_ || current_seq_.request_))
        {
          current_seq_.make_seq_ = true;
          current_seq_.id_seq_   = boost::uuids::random_generator () ();
        }
      return IEvent::ptr ();
    }

  return IEvent::ptr ();
}

}}}}      // namespace libs::ilink::appl::root
