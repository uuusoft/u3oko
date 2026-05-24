/**
\file       root-module-catch-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "root-module.hpp"

namespace libs::ilink::appl::root
{
syn::IEvent::ptr
RootModule::default_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  try
  {
    if (forward)
    {
      //  Если сообщение уже пришло с транзакцией, значит это ответ на нашу транзакцию.
      if (current_seq_.recv_seq_)
      {
        U3_ASSERT (current_seq_.answer_);
        return syn::IEvent::ptr ();
      }

      U3_ASSERT (!current_seq_.dest_);
      current_seq_.dest_ = get_dest_link (msg);   //  Ищем модуль будет обрабатывать данное сообщение и, если модуль существует, помечаем сообщение для транзакции.

      if (current_seq_.dest_ && (current_seq_.sync_event_ || current_seq_.request_))
      {
        //  инициируем новую транзакцию.
        current_seq_.make_seq_ = true;
        current_seq_.id_seq_   = boost::uuids::random_generator () ();
        // U3_XLOG_DEV ("catch seq msg " << current_seq_.id_seq_.name ());
      }

      return syn::IEvent::ptr ();
    }
  }
  catch (const std::exception& e)
  {
    U3_XLOG_ERROR ("RootModule::default_catch_func" + TOLOG (text_id_module_) + std::string (e.what ()) + TOLOG (msg->get_mid ()));
  }
  return syn::IEvent::ptr ();
}
}   // namespace libs::ilink::appl::root
