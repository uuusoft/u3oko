/**
\file       root-module-basemodule.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
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

          auto cffinger = catch_funcs_.end ();
          for (const auto& cmsg : cmsgs)
          {
            if (!cmsg.first)
            {
              continue;
            }

            cffinger = catch_funcs_.find (cmsg.second);
            if (catch_funcs_.end () != cffinger)
            {
              break;
            }
          }

          catch_msg_func_type nfunc =
            catch_funcs_.end () != cffinger ?
              cffinger->second :
              [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
                // U3_XLOG_DBG ("RootModule::appl_work_int::default catch" + TOLOG (msg->gen_get_mid ()) + VTOLOG (forward));
                if (forward)
                {
                  // Если сообщение уже пришло с транзакцией, значит это ответ на нашу транзакцию
                  if (current_seq_.recv_seq_)
                  {
                    U3_ASSERT (current_seq_.answer_);
                    return syn::IEvent::ptr ();
                  }

                  U3_ASSERT (!current_seq_.dest_);
                  // Ищем модуль будет обрабатывать данное сообщение и, если модуль существует, помечаем сообщение для транзакции
                  current_seq_.dest_ = get_dest_link (msg);
                  if (current_seq_.dest_ && (current_seq_.sync_event_ || current_seq_.request_))
                  {
                    //  инициируем новую транзакцию.
                    current_seq_.make_seq_ = true;
                    current_seq_.id_seq_   = boost::uuids::random_generator () ();
                    U3_XLOG_DBG ("make new trans event" + TOLOG (to_string (current_seq_.id_seq_)));
                  }
                }
                return syn::IEvent::ptr ();
              };

          funcs.push_back (std::make_pair (nfunc, msg));

          try
          {
            msg = nfunc (msg, true, current_seq_);
          }
          catch (const std::exception& excpt)
          {
            U3_LOG_APPL_EXCEPT (excpt.what ());
            msg = syn::IEvent::ptr ();
          }

          last_msg = msg ? msg : last_msg;
        }

        const bool seqs_exist   = current_seq_.recv_seq_ || current_seq_.make_seq_;
        auto       src_complite = src;
        // U3_XLOG_DBG (VTOLOG (current_seq_.answer_) + VTOLOG (seqs_exist) + VTOLOG (current_seq_.recv_seq_));
        // Если это не часть последовательности и ответ, то это ответ данному модулю на его же запрос -
        // ничего никуда не пересылаем - запрос уже обработан
        if (current_seq_.answer_ && !seqs_exist)
        {
          // U3_XLOG_DBG ("allready done...");
        }
        else
        {
          // Если данное сообщение является частью транзакции.
          if (seqs_exist)
          {
            //  1. Смотрим на уже существующие транзакции, и если данная одна из них - завершаем
            if (current_seq_.recv_seq_)
            {
              current_seq_.source_ = src;

              auto seqfinger = seqs_.find (current_seq_);
              U3_ASSERT (seqfinger != seqs_.end ());
              src_complite = seqfinger->source_;
              seqs_.erase (seqfinger);
            }
            // 2. Иначе, добавляем данную транзакцию в список существующих и пересылаем сообщение дальше, соответствующему модулю
            else
            // if (current_seq_.make_seq_)
            {
              current_seq_.source_ = src;
              U3_ASSERT (seqs_.find (current_seq_) == seqs_.end ());
              seqs_.insert (current_seq_);
              src_complite.reset ();
            }
          }
          // если это не ответное сообщение и не часть транзакции - просто пересылаем его дальше
          else
          {
            if (current_seq_.dest_)   //< ДЛЯ ОТЛАДКИ, надо правильно перенаправлять FrameDone!!!
            {
              U3_ASSERT (current_seq_.dest_);
              src_complite.reset ();
            }
          }
          // Если сообщение часть транзакции, но модуль-обработчик не определен, это выглядит как ошибка
          // Пока просто обрабатваем такую ситуацию так
          if (!src_complite && !current_seq_.dest_)
          {
            U3_ASSERT_SIGNAL_NT ("[!src_complite && !current_seq_.dest_]");
            src_complite = src;
          }
          // Если сообщение не часть транзакции - завершаем его через источник
          if (src_complite)
          {
            U3_XLOG_DBG ("complite event by source" + TOLOG (to_string (current_seq_.id_seq_)));
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
              U3_XLOG_DBG ("send transaction msg to leaf" + VTOLOG (seqs_exist));
              auto seq_msg = ::libs::events::helpers::wrap_seq_msg (recv_msg, current_seq_.id_seq_);
              current_seq_.dest_->send_msg (seq_msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
            }
            else
            {
              current_seq_.dest_->send_msg (recv_msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
            }
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
    catch (const std::exception& excpt)
    {
      U3_LOG_APPL_EXCEPT (excpt.what ());
    }
  } while (true);
}


bool
RootModule::appl_deinit_int ()
{
  U3_XLOG_DBG ("RootModule::appl_deinit_int::---->")
  bool ret = false;

  switch (deinit_stage_)
  {
  case DeInitStages::send_stop_msg2allmost_all: {
    if (links_.get (syn::mids::appl2log))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

      dmsg->change_appl_info (
        ::libs::ilog_events::AppllPartLogInfo (
          ::libs::ievents::props::modules::log::LogLevels::info,
          appl_info_.appl_name_,
          ::libs::helpers::log::get_module_version ()),
        "");

      dmsg->set_start (false);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    if (links_.get (syn::mids::appl2gui))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::igui_events::events::ExitApplEvent > (rmsg);
      links_.get (syn::mids::appl2gui)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    change_module_state (links_.get (syn::mids::appl2http), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2mdata), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2gui), appl_info_.appl_name_, false);

    // std::this_thread::sleep_for (std::chrono::milliseconds (10 * 1000)); // debug
    deinit_stage_ = DeInitStages::wait_stop_data_module;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  case DeInitStages::wait_stop_data_module: {
    if (!links_.get (syn::mids::appl2mdata) || !links_.get (syn::mids::appl2mdata)->is_connected ())
    {
      change_module_state (links_.get (syn::mids::appl2events), appl_info_.appl_name_, false);
      change_module_state (links_.get (syn::mids::appl2storage), appl_info_.appl_name_, false);

      links_.reset_link (syn::mids::appl2mdata);
      deinit_stage_ = DeInitStages::wait_stop_gui_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    ++deinit_stage_counter_;
    break;
  }
  case DeInitStages::wait_stop_gui_module: {
    if (!links_.get (syn::mids::appl2gui) || !links_.get (syn::mids::appl2gui)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2gui);
      deinit_stage_ = DeInitStages::wait_stop_storage_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
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
  U3_XLOG_DBG ("RootModule::appl_deinit_int::<----")
  return ret;
}


void
RootModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  // Функция обработчик сообщения транзакции
  catch_funcs_[::libs::events::ISeqEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* seq_ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISeqEvent > (msg);
      auto  ret     = seq_ret->get_msg ();

      U3_ASSERT (ret);
      current_seq_.recv_seq_ = true;
      current_seq_.id_seq_   = seq_ret->get_seq_id ();
      return ret;
    }
    return syn::IEvent::ptr ();
  };

  // Функция обработчик сообщения признака синхронности
  catch_funcs_[::libs::events::ISyncEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      current_seq_.sync_event_ = true;

      auto ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISyncEvent > (msg)->get_msg ();
      U3_ASSERT (ret);
      return ret;
    }

    if (::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg))
    {
      return msg;
    }
    return syn::IEvent::ptr ();
  };

  // Функция обработчик сообщения признака запроса
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
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::events::IAnswerEvent > (rmsg);
    dmsg->set_msg (msg);
    return rmsg;
  };

  // Функция обработчик сообщения признака ответа на запрос
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

  catch_funcs_[syn::ApplicationProp::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_);
      U3_XLOG_DEV ("copy::---->" + TOLOG (main_appl->get_messenger_impl ()) + PTR_TOLOG (main_appl));
      msg->copy (main_appl);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::InfoCPUEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);
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

  catch_funcs_[syn::PropertyLogModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* info_log = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
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

  catch_funcs_[syn::WrapperEventsEvent::gen_get_mid ()] =
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

  catch_funcs_[syn::ExpandTimesEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto res = links_.get (syn::mids::appl2mdata)->send_msg (msg, ::libs::link::details::CallSyncs::sync, ::libs::link::details::Calls::set);
      return syn::IEvent::ptr ();
    }
    return msg;
  };
}


void
RootModule::init_proxys_int ()
{
  U3_XLOG_DBG ("RootModule::init_proxys_int::---->");
  super::init_proxys_int ();
#if 0
  {
    U3_XLOG_DBG ("BaseModule::init_proxys_int:: update shared propertyes");
    auto orinfo = ::libs::iproperties::helpers::cast_prop_demons ();

    syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
    orinfo->set_bufs_lockfree (all2buf_);
    orinfo->set_mem_lockfree (all2mem_);
    orinfo->set_optim_lockfree (all2optim_);
    orinfo->set_events_lockfree (all2events_);
  }

  U3_XLOG_DBG ("RootModule::init_proxys_int:: update appl event props");
  appl_event_props_.init ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "instance mem block allocator");
#endif
  U3_XLOG_DBG ("RootModule::init_proxys_int::<----");
}


void
RootModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_XLOG_DBG ("RootModule::init_links_int::--->");
  auto*      main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_.get ());
  const auto type_run  = main_appl->is_single_process () ? ::libs::link::details::CodeRuns::dll : ::libs::link::details::CodeRuns::appl;
  auto       lproxy    = LinkCreatorProxy::instance ();
  auto       iproxy    = lproxy->impl ();
  auto       ipstorage = ::libs::iproperties::helpers::get_storage ();

  const std::tuple< std::string, std::string, ::libs::link::details::ModuleLinks, std::uint32_t, syn::mids::key_storage_type > create_vals[] = {
    { "mpl_mlog", "subsys_appl2log", ::libs::link::details::ModuleLinks::log, ::libs::link::consts::sizes::buf_all2log, syn::mids::appl2log },
    { "mpl_mevents", "subsys_events", ::libs::link::details::ModuleLinks::events, ::libs::link::consts::sizes::buf_all2events, syn::mids::appl2events },
    { "mpl_mstorage", "subsys_storage", ::libs::link::details::ModuleLinks::storage, ::libs::link::consts::sizes::buf_appl2storage, syn::mids::appl2storage },
    { "mpl_mdata", "subsys_data", ::libs::link::details::ModuleLinks::mdata, ::libs::link::consts::sizes::buf_appl2data, syn::mids::appl2mdata },
    { "mpl_mhttp", "subsys_http", ::libs::link::details::ModuleLinks::http, ::libs::link::consts::sizes::buf_appl2http, syn::mids::appl2http }
#if (U3_MODULES_ENABLE_GUI == 1)
    ,
    { "mpl_mgui", "subsys_gui", ::libs::link::details::ModuleLinks::gui, ::libs::link::consts::sizes::buf_appl2gul, syn::mids::appl2gui }
#endif
  };

  // Устанавливаем контейнер для получения связей от модулей
  ipstorage->set_prop (
    ::libs::properties::consts::keys::links_property,
    std::make_shared< syn::ILinksProperty > (syn::ILinksProperty::links_type {}));

  constexpr std::uint32_t dbg_delay_process = 3000;
  std::uint32_t           create_counter    = 0;
  for (const auto& [dll_name, subsys_name, subsys_id, buf_size, link_id] : create_vals)
  {
    // U3_XLOG_DEV ("debug sleep::---->" + VTOLOG (create_counter) + TOLOG (dll_name));
    // std::this_thread::sleep_for (std::chrono::milliseconds (dbg_delay_process));
    // U3_XLOG_DEV ("debug sleep::<----" + VTOLOG (create_counter) + TOLOG (dll_name));
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "mappl.exe",
        dll_name,
        appl_info_.company_name_,
        appl_info_.appl_name_,
        subsys_name,
        subsys_id,
        buf_size));

    links_.set (link_id, temp_link);
    ++create_counter;
  }

  //  Разделяем созданные интерфейсы между всей системой через объект "свойства"
  {
    // std::this_thread::sleep_for (std::chrono::milliseconds (dbg_delay_process));
    // U3_XLOG_DEV (PTR_TOLOG (links_.get (syn::mids::appl2log).get ()));
    auto* ilinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links  = ilinks->update_links_lockfree ();
    for (const auto& [dll_name, subsys_name, subsys_id, buf_size, link_id] : create_vals)
    {
      links.set (link_id, links_.get (link_id));
    }
  }

  {
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

    dmsg->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        appl_info_.appl_name_,
        ::libs::helpers::log::get_module_version ()),
      "");

    dmsg->set_start (true);
    links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::PropertyStorageModuleEvent > (rmsg);
    links_.get (syn::mids::appl2storage)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    syn::TextExtCpu helper;
    auto*           info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);

    U3_LOG_APPL_MARK ("CPU ext       : " + helper.get_text (info_cpu->get_cpu_type ()));
    U3_LOG_APPL_MARK ("Cores count   : " + std::to_string (info_cpu->get_cpu_count ()));
    U3_LOG_APPL_MARK ("Threads count : " + std::to_string (::libs::optim::mcalls::get_count_work_threads_by_count_cpu (info_cpu->get_cpu_count ())));

    links_.get (syn::mids::appl2mdata)->send_msg (appl_event_props_.info_cpu_, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  const std::tuple< syn::mids::key_storage_type > start_vals[] = {
    { syn::mids::appl2log },
    { syn::mids::appl2events },
    { syn::mids::appl2storage },
    { syn::mids::appl2mdata },
    { syn::mids::appl2http }
#if (U3_MODULES_ENABLE_GUI == 1)
    ,
    { syn::mids::appl2gui }
#endif
  };

  for (const auto& [link_id] : start_vals)
  {
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);
    dmsg->set_start (true);
    links_.get (link_id)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
  U3_XLOG_DBG ("RootModule::init_links_int::<----");
}
}   // namespace libs::ilink::appl::root
