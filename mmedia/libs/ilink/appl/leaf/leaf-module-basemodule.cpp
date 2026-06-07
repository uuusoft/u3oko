/**
\file       leaf-module-basemodule-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
void
LeafModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::ISeqEvent::gen_get_mid (),
      std::bind (&LeafModule::seq_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::ISyncEvent::gen_get_mid (),
      std::bind (&LeafModule::sync_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::IRequestEvent::gen_get_mid (),
      std::bind (&LeafModule::request_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::IAnswerEvent::gen_get_mid (),
      std::bind (&LeafModule::answer_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      syn::ChangeStateProcessEvent::gen_get_mid (),
      [this] (::libs::events::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> ::libs::events::IEvent::ptr {
        try
        {
          if (forward)
          {
            auto state_cmd = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
            if (!state_cmd->is_start ())
            {
              stop_module_ = true;
            }
            return ::libs::events::IEvent::ptr ();
          }
          return msg;
        }
        catch (const std::exception& e)
        {
          U3_LOG_APPL_EXCEPT (e.what ());
        }
        return ::libs::events::IEvent::ptr ();
      }));
}

// EAI-REFACT function
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
        auto msg     = src ? src->received_msg () : ::libs::events::IEvent::ptr ();
        auto deb_msg = msg;   // debug
        if (!msg)
        {
          continue;
        }

        recv_msg      = true;
        auto last_msg = msg;

        //  Прямая сборка стека функций для обработки данного сообщения.
        //  Формируем описание запроса (все флаги, транзакцию и прочее).
        while (msg)
        {
          std::pair< ::libs::events::IEvent::raw_ptr, ::libs::events::IEvent::hid_type > cmsgs[] = {
            { msg.get (), msg->get_mid () },
            { ::libs::iproperties::helpers::cast_event< ievents::runtime::RuntimeEvent > (msg), ievents::runtime::RuntimeEvent::gen_get_mid () },
            { ::libs::iproperties::helpers::cast_event< ::libs::ilog_events::events::InfoLogEvent > (msg), ::libs::ilog_events::events::InfoLogEvent::gen_get_mid () }
          };

          auto find = catch_funcs_.end ();
          for (const auto& cmsg : cmsgs)
          {
            if (!cmsg.first)
            {
              continue;
            }

            find = catch_funcs_.find (cmsg.second);
            if (catch_funcs_.end () != find)
            {
              break;
            }
          }

          catch_msg_func_type funct = std::bind (
            &LeafModule::default_catch_func,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

          if (catch_funcs_.end () != find)
          {
            funct = find->second;
          }

          funcs.push_back (std::make_pair (funct, msg));

          try
          {
            msg = funct (msg, true, current_seq_);
          }
          catch (const std::exception& e)
          {
            U3_LOG_APPL_EXCEPT (e.what ());
            msg = ::libs::events::IEvent::ptr ();
          }

          last_msg = msg ? msg : last_msg;
        }


        if (!catch_event (last_msg))
        {
        }

        U3_ASSERT (!funcs.empty ());
        auto src_complite = src;

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
        catch (const std::exception& e)
        {
          U3_LOG_APPL_EXCEPT (e.what ());
        }

        // сброс переменных вне цикла.
        current_seq_.reset ();
        funcs.clear ();
      }

      if (is_now_thread_to_sleep (recv_msg))
      {
        if (ms_time_sleep_ > 0)
        {
          std::this_thread::sleep_for (std::chrono::milliseconds (ms_time_sleep_));
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
    catch (const std::exception& e)
    {
      U3_LOG_APPL_EXCEPT (e.what ());
    }
  } while (true);

  appl_deinit ();
}
}   // namespace libs::ilink::appl::leaf
