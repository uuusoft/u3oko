/**
\file       root-module-work-funct.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "root-module.hpp"

namespace libs::ilink::appl::root
{
void
dump_state ()
{
  const auto prop_demons  = ::libs::iproperties::helpers::cast_prop_demons ();
  const auto memory_state = prop_demons->get_mem_lockfree ()->impl ()->dump_memory_status ();
  const auto bufs_state   = prop_demons->get_bufs_lockfree ()->impl ()->dump_bufs_state ();

  U3_LOG_APPL_MARK ("memory status:" + memory_state);
  U3_LOG_APPL_MARK ("buf status:" + bufs_state);
}


// EAI-REFACT function
void
RootModule::appl_work_int ()
{
  ::libs::helpers::thread::set_thread_priority (std::this_thread::get_id (), ::libs::helpers::thread::Priorities::high);

  do
  {
    try
    {
      bool                     now_recv_msg  = false;
      const auto               now           = boost::posix_time::microsec_clock::universal_time ();
      const auto               duration_time = now - time_dump_status_;
      recv_links_type          srss          = get_recv_link ();
      list_catch_msg_func_type funcs;

      if (duration_time.minutes () >= consts::minute_period_dump_state)
      {
        dump_state ();
        time_dump_status_ = now;
      }

      for (::libs::link::ILink::ptr& src : srss)
      {
        auto recv_msg = src ? src->received_msg () : syn::IEvent::ptr ();
        auto msg      = recv_msg;

        if (!msg)
        {
          continue;
        }

        now_recv_msg = true;

        auto last_msg = msg;

        //  Сборка стека функций для обработки данного сообщения
        while (msg)
        {
          std::pair< syn::IEvent::raw_ptr, syn::IEvent::hid_type > cmsgs[] = {
            { msg.get (), msg->get_mid () },
            { ::libs::iproperties::helpers::cast_event< ievents::runtime::RuntimeEvent > (msg), ievents::runtime::RuntimeEvent::gen_get_mid () }
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
              std::bind (&RootModule::default_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

          funcs.push_back (std::make_pair (nfunc, msg));
          msg      = nfunc (msg, true, current_seq_);
          last_msg = msg ? msg : last_msg;
        }

        const bool seqs_exist   = current_seq_.recv_seq_ || current_seq_.make_seq_;
        auto       src_complite = src;
        // Если это не часть последовательности и ответ, то это ответ данному модулю на его же запрос - ничего никуда не пересылаем - запрос уже обработан.
        if (current_seq_.answer_ && !seqs_exist)
        {
          // boo!
        }
        else
        {
          // Если данное сообщение является частью транзакции.
          if (seqs_exist)
          {
            //  1. Смотрим на уже существующие транзакции, и если данная одна из них - завершаем.
            if (current_seq_.recv_seq_)
            {
              current_seq_.source_ = src;

              auto finger = seqs_.find (current_seq_);
              U3_ASSERT (finger != seqs_.end ());

              src_complite = finger->source_;
              seqs_.erase (finger);
            }
            // 2. Иначе, добавляем данную транзакцию в список существующих и пересылаем сообщение дальше, соответствующему модулю.
            else
            // if (current_seq_.make_seq_)
            {
              current_seq_.source_ = src;
              U3_ASSERT (seqs_.find (current_seq_) == seqs_.end ());
              seqs_.insert (current_seq_);
              src_complite.reset ();
            }
          }
          // если это не ответное сообщение и не часть транзакции - просто пересылаем его дальше.
          else
          {
            if (current_seq_.dest_)   //< ДЛЯ ОТЛАДКИ, надо правильно перенаправлять FrameDone!!!
            {
              U3_ASSERT (current_seq_.dest_);
              src_complite.reset ();
            }
          }
          // Если сообщение часть транзакции, но модуль-обработчик не определен, это выглядит как ошибка.
          // Пока просто обрабатваем такую ситуацию так.
          if (!src_complite && !current_seq_.dest_)
          {
            U3_ASSERT_SIGNAL ("[!src_complite && !current_seq_.dest_]");
            src_complite = src;
          }
          // Если сообщение не часть транзакции - завершаем его через источник.
          if (src_complite)
          {
            U3_ASSERT (!funcs.empty ());
            src_complite->complite_msg (last_msg, current_seq_);
          }
          // Иначе,
          // 1. Добавляем транзакцию для того сообщения, которое нам пришло изначально
          // 2. Чистим сообщение синхронности.
          // 3. Передаем сообщение в найденный модуль
          else
          {
            U3_ASSERT (current_seq_.dest_);
            if (seqs_exist)
            {
              auto seq_msg = ::libs::events::helpers::wrap_seq_msg (recv_msg, current_seq_.id_seq_);
              current_seq_.dest_->send_msg (
                seq_msg,
                ::libs::link::details::CallSyncs::async,
                ::libs::link::details::Calls::set);
            }
            else
            {
              current_seq_.dest_->send_msg (
                recv_msg,
                ::libs::link::details::CallSyncs::async,
                ::libs::link::details::Calls::set);
            }
            // current_seq_.dest_->send_msg ( last_msg );
          }
        }
        // сброс внешних к циклу переменных
        {
          current_seq_.reset ();
          funcs.clear ();
        }
      }
      // Если в данной итерации не обработано ни одного сообщения - засыпаем на определенный интервал
      if (!now_recv_msg)
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
        //  ждем остановки всех зависимых модулей.
        if (appl_deinit ())
        {
          U3_XLOG_MARK ("RootModule::appl_work_int: appl_deinit ok" + TOLOG (text_id_module_));
          break;
        }
      }
    }
    catch (const std::exception& e)
    {
      U3_LOG_APPL_EXCEPT (e.what ());
    }
  } while (true);
}
}   // namespace libs::ilink::appl::root
