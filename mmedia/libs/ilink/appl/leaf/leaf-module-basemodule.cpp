/**
\file       leaf-module-basemodule.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
void
LeafModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[::libs::events::ISeqEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* seq_ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISeqEvent > (msg);
      auto  ret     = seq_ret->get_msg ();

      U3_ASSERT (ret);
      U3_ASSERT (!seq_ret->get_seq_id ().empty ());

      current_seq_.recv_seq_ = true;
      current_seq_.id_seq_   = seq_ret->get_seq_id ();
      return ret;
    }

    U3_ASSERT (current_seq_.request_);   //  это должен быть запрос, иначе быссмысленно.
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< ::libs::events::ISeqEvent > ();
    // для конечного модуля, если пришло сообщение  с идентификатором, используем его для ответа
    // И изначальное сообщение должно быть запросом
    revnt->set_msg (msg);
    revnt->set_seq_id (current_seq_.id_seq_);
    return evnt;
  };

  // Функция обработчик сообщения признака синхронности
  catch_funcs_[::libs::events::ISyncEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISyncEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }
    if (::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg))
    {
      return msg;
    }
    return {};
  };

  catch_funcs_[::libs::events::IRequestEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      current_seq_.request_ = true;
      auto ret              = ::libs::iproperties::helpers::cast_event< ::libs::events::IRequestEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }

    //  инверсия, на запрос идет ответ.
    auto [evnt, revnt] = libs::iproperties::helpers::create_event< ::libs::events::IAnswerEvent > ();
    revnt->set_msg (msg);
    return evnt;
  };

  catch_funcs_[::libs::events::IAnswerEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      current_seq_.answer_ = true;
      auto ret             = ::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }
    //  инверсия, пришел ответ модулю
    return msg;
  };

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* state_cmd = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      if (!state_cmd->is_start ())
      {
        stop_module_ = true;
      }
      return {};
    }
    return msg;
  };
}

// EAI-REFACT
void
LeafModule::appl_work_int ()
{
  do
  {
    try
    {
      list_catch_msg_func_type funcs;
      recv_links_type          srss     = get_recv_link ();
      bool                     recv_msg = false;

      for (auto& src : srss)
      {
        if (!src)
        {
          continue;
        }
        auto msg = src->received_msg ();
        if (!msg)
        {
          continue;
        }
        if (dbg_event_cycle_)
        {
          U3_XLOG_DEV ("debug event cycle");
        }

        recv_msg      = true;
        auto last_msg = msg;

        //  Прямая сборка стека функций для обработки данного сообщения.
        //  Формируем описание запроса (все флаги, транзакцию и прочее).
        while (msg)
        {
          std::pair< syn::IEvent::raw_ptr, syn::IEvent::hid_type > cmsgs[] = {
            { msg.get (), msg->get_mid () },
            { ::libs::iproperties::helpers::cast_event< events_base::runtime::RuntimeEvent > (msg), events_base::runtime::RuntimeEvent::gen_get_mid () },
            { ::libs::iproperties::helpers::cast_event< ::libs::events_log::events::InfoLogEvent > (msg), ::libs::events_log::events::InfoLogEvent::gen_get_mid () }
          };

          auto ffinger = catch_funcs_.end ();
          for (const auto& cmsg : cmsgs)
          {
            if (!cmsg.first)
            {
              continue;
            }

            ffinger = catch_funcs_.find (cmsg.second);
            if (catch_funcs_.end () != ffinger)
            {
              break;
            }
          }

          catch_msg_func_type nfunc =
            catch_funcs_.end () != ffinger ?
              ffinger->second :
              [] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
            U3_XLOG_DBG ("LeafModule::appl_work_int::default catch" + TOLOG (msg->gen_get_mid ()));
            return syn::IEvent::ptr ();
          };

          funcs.emplace_back (nfunc, msg);

          try
          {
            msg = nfunc (msg, true, current_seq_);
          }
          catch (const std::exception& excpt)
          {
            U3_XLOG_ERROR (excpt.what ());
            // U3_LOG_APPL_EXCEPT (excpt.what());
            msg = syn::IEvent::ptr ();
          }

          last_msg = msg ? msg : last_msg;
        }


        U3_XLOG_DBG ("before catch_event");
        if (!catch_event (last_msg))
        {
        }

        U3_ASSERT (!funcs.empty ());
        const auto& src_complite = src;

        try
        {
          // Если конечному модулю пришел ответ, ненадо пересылать его дальше. Ответа на ответ не существует.
          // Если это и не был запрос (а установка), опять же ничего пересылать не надо.
          // U3_XLOG_DEV ("current_seq_.answer_=" << current_seq_.answer_ << " current_seq_.request_=" << current_seq_.request_);
          if (!current_seq_.answer_ && current_seq_.request_)
          {
            src->complite_msg (last_msg, current_seq_);
          }
          //  Если сообщение не часть транзакции - завершаем его через источник
          if (!current_seq_.is_seq_exist ())
          {
            funcs.clear ();
            src_complite->complite_msg (last_msg, current_seq_);
          }
        }
        catch (const std::exception& excpt)
        {
          U3_XLOG_ERROR (excpt.what ());
          // U3_LOG_APPL_EXCEPT (excpt.what());
        }

        // сброс переменных вне цикла.
        current_seq_.reset ();
        funcs.clear ();
      }

      if (is_now_thread_to_sleep (recv_msg))
      {
        if (ms_time_sleep_.count () > 0)
        {
          std::this_thread::sleep_for (ms_time_sleep_);
        }
        else
        {
          std::this_thread::yield ();
        }
      }

      if (stop_module_)
      {
        U3_XLOG_DEV ("LeafModule::appl_work_int: stop module recived" + TOLOG (text_id_module_));
        break;
      }
    }
    catch (const std::exception& excpt)
    {
      // U3_LOG_APPL_EXCEPT (excpt.what());
      U3_XLOG_ERROR (excpt.what ());
    }
  } while (true);

  appl_deinit ();
}
}   // namespace libs::ilink::appl::leaf
