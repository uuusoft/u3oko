/**
\file       root-module-basemodule.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
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


void
change_module_state (
  const RootModule::links_type::link_ptr_type& link,
  const std::string&                           name_appl,
  bool                                         state)
{
  if (!link)
  {
    return;
  }

  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

#ifdef U3_FAKE_DISABLE
  dmsg->change_appl_info (
    ::libs::ilog_events::AppllPartLogInfo (
      ::libs::ievents::props::modules::log::LogLevels::info,
      name_appl,
      ::libs::helpers::log::get_module_version ()),
    "");
#endif

  dmsg->set_start (state);
  link->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
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
          // Если сообщение часть транзакции, но модуль-обработчик не определен, это выглядит как ошибка
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
          // 2. Чистим сообщение синхронности
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


bool
RootModule::appl_deinit_int ()
{
  bool ret = false;

  switch (deinit_stage_)
  {
  case DeInitStages::send_stop_msg2allmost_all: {
    if (links_.get (syn::mids::appl2log))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

      dmsg->change_appl_info (
        ::libs::ilog_events::AppllPartLogInfo (
          ::libs::ievents::props::modules::log::LogLevels::info,
          appl_info_.appl_name_,
          ::libs::helpers::log::get_module_version ()),
        "");

      dmsg->set_start (false);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    change_module_state (links_.get (syn::mids::appl2http), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2mdata), appl_info_.appl_name_, false);

#ifdef U3_GUI_ENABLE
    change_module_state (links_.get (syn::mids::appl2gui), appl_name_, false);
    if (links_.get (syn::mids::appl2gui))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::igui_events::events::ExitApplEvent > (rmsg);
      links_.get (syn::mids::appl2gui)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }
#endif

    change_module_state (links_.get (syn::mids::appl2events), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2storage), appl_info_.appl_name_, false);
    // std::this_thread::sleep_for (std::chrono::milliseconds (10 * 1000)); // debug
    deinit_stage_ = DeInitStages::wait_stop_data_module;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  case DeInitStages::wait_stop_data_module: {
    if (!links_.get (syn::mids::appl2mdata) || !links_.get (syn::mids::appl2mdata)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2mdata);
#ifdef U3_GUI_ENABLE
      deinit_stage_ = DeInitStages::wait_stop_gui_module;
#else
      deinit_stage_ = DeInitStages::wait_stop_storage_module;
#endif
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    ++deinit_stage_counter_;
    break;
  }
#ifdef U3_GUI_ENABLE
  case DeInitStages::wait_stop_gui_module: {
    if (!links_.get (syn::mids::appl2gui) || !links_.get (syn::mids::appl2gui)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2gui);
      deinit_stage_         = DeInitStages::wait_stop_storage_module;
      deinit_stage_counter_ = 0;
    }
    break;
  }
#endif
  case DeInitStages::wait_stop_storage_module: {
    if (!links_.get (syn::mids::appl2storage) || !links_.get (syn::mids::appl2storage)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2storage);
      deinit_stage_ = DeInitStages::wait_stop_events_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::wait_stop_events_module: {
    if (!links_.get (syn::mids::appl2events) || !links_.get (syn::mids::appl2events)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2events);
      deinit_stage_ = DeInitStages::send_stop_msg2log_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::send_stop_msg2log_module: {
    if (links_.get (syn::mids::appl2log))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

      dmsg->set_start (false);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    deinit_stage_ = DeInitStages::wait_stop_log_module;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  case DeInitStages::wait_stop_log_module: {
    if (!links_.get (syn::mids::appl2log) || !links_.get (syn::mids::appl2log)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2log);
      deinit_stage_ = DeInitStages::done;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::done: {
    ret = true;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  default:
    U3_ASSERT_SIGNAL ("Unknown deinit stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)));
    break;
  }
  return ret;
}


void
RootModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[::libs::events::ISeqEvent::gen_get_mid ()] = std::bind (
    &RootModule::seq_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::ISyncEvent::gen_get_mid ()] = std::bind (
    &RootModule::sync_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::IRequestEvent::gen_get_mid ()] = std::bind (
    &RootModule::request_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::IAnswerEvent::gen_get_mid ()] = std::bind (
    &RootModule::answer_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[syn::ApplicationProp::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_);
      msg->copy (main_appl);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::InfoCPUEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);
      if (process_state.request_)
      {
        msg->copy (info_cpu);
      }
      else if (!process_state.answer_)
      {
        syn::TextExtCpu helper;
        info_cpu->copy (msg.get ());
        U3_LOG_APPL_MARK ("updated cpu: " + helper.get_text (info_cpu->get_cpu_type ()) + " {" + std::to_string (info_cpu->get_cpu_count ()) + "}");
        links_.get (syn::mids::appl2mdata)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);

        const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
        helpers::save_event_to_json_file (active_paths, msg);
      }
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[::libs::ievents::props::modules::log::PropertyLogModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto info_log = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::modules::log::PropertyLogModuleEvent > (appl_event_props_.module_log_);
      if (process_state.request_)
      {
        msg->copy (info_log);
      }
      else if (!process_state.answer_)
      {
        info_log->copy (msg.get ());
        ::libs::ievents::props::modules::log::g_log_level = ::libs::ievents::props::modules::log::from_raw_val (info_log->get_val (::libs::ievents::props::modules::log::LogVals::log_level));
        links_.get (syn::mids::appl2log)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);

        const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
        helpers::save_event_to_json_file (active_paths, msg);
      }
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[::libs::ievents_events::events::WrapperEventsEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      if (!process_state.answer_)
      {
        links_.get (syn::mids::appl2events)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
        // const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
        // helpers::save_event_to_file (active_paths, msg);
      }
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[::libs::ievents::runtime::state::ExpandTimesEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto res = links_.get (syn::mids::appl2mdata)->send_msg (msg, ::libs::link::details::CallSyncs::sync, ::libs::link::details::Calls::set);
      return syn::IEvent::ptr ();
    }
    return msg;
  };
}
}   // namespace libs::ilink::appl::root
