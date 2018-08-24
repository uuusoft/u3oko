//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       root-module-work-funct.cpp
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

void
RootModule::work_int ()
{
  try
    {
      recv_links_type           _srss = get_recv_link ();
      list_catch_msg_funct_type _functs;

      do
        {
          bool       _now_recv_msg  = false;
          const auto _now_time      = boost::posix_time::microsec_clock::universal_time ();
          const auto _duration_time = _now_time - last_time_dump_status_system_;

          if (_duration_time.minutes () >= 1)
            {
              ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->dump_status ();
              ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ()->dump_state ();
              last_time_dump_status_system_ = _now_time;
            }

          for (ILink::ptr& _src : _srss)
            {
              auto _recv_msg = _src ? _src->received_msg () : IEvent::ptr ();
              auto _msg      = _recv_msg;

              if (!_msg)
                {
                  continue;
                }

              _now_recv_msg = true;

              auto _last_msg = _msg;
              //  Сборка стека функций для обработки данного сообщения.
              while (_msg)
                {
                  std::pair<IEvent::raw_ptr, IEvent::text_id_type> _cmsgs[] = {
                    { _msg.get (), _msg->get_mid () },
                    { ::libs::iproperties::helpers::cast_event<ievents::runtime::RuntimeEvent> (_msg), ievents::runtime::RuntimeEvent::gen_get_type_text_id () }
                  };

                  auto _find = catch_functs_.end ();
                  for (const auto& _cmsg : _cmsgs)
                    {
                      if (!_cmsg.first)
                        {
                          continue;
                        }

                      _find = catch_functs_.find (_cmsg.second);
                      if (catch_functs_.end () != _find)
                        {
                          break;
                        }
                    }

                  catch_msg_funct_type _funct = std::bind (&RootModule::default_catch_funct, this, std::placeholders::_1, std::placeholders::_2);
                  if (catch_functs_.end () != _find)
                    {
                      _funct = _find->second;
                    }

                  _functs.push_back (std::make_pair (_funct, _msg));
                  _msg      = _funct (_msg, true);
                  _last_msg = _msg ? _msg : _last_msg;
                }

              XULOG_TRACE (text_id_module_ << ", root: msg received, " << helpers::to_str (current_seq_) << ", " << _last_msg->get_mid ());
              const bool _seqs_exist   = current_seq_.recv_seq_ || current_seq_.make_seq_;
              auto       _src_complite = _src;
              //  Если это не часть последовательности и ответ, то это ответ данному модулю на его же запрос - ничего никуда не пересылаем - запрос уже обработан.
              if (current_seq_.answer_ && !_seqs_exist)
                {
                  //boo!
                }
              else
                {
                  //  Если данное сообщение является частью транзакции.
                  if (_seqs_exist)
                    {
                      //  1. Смотрим на уже существующие транзакции, и если данная одна из них - завершаем.
                      if (current_seq_.recv_seq_)
                        {
                          current_seq_.source_ = _src;

                          auto _find_it = seqs_.find (current_seq_);
                          UASSERT (_find_it != seqs_.end ());

                          _src_complite = _find_it->source_;
                          seqs_.erase (_find_it);
                        }
                      //  2. Иначе, добавляем данную транзакцию в список существующих и пересылаем сообщение дальше, соответствующему модулю.
                      else
                        //if (current_seq_.make_seq_)
                        {
                          current_seq_.source_ = _src;
                          UASSERT (seqs_.find (current_seq_) == seqs_.end ());
                          seqs_.insert (current_seq_);
                          _src_complite.reset ();
                        }
                    }
                  //  если это не ответное сообщение и не часть транзакции - просто пересылаем его дальше.
                  else
                    {
                      if (current_seq_.dest_)      //< ДЛЯ ОТЛАДКИ, надо правильно перенаправлять FrameDone!!!
                        {
                          UASSERT (current_seq_.dest_);
                          _src_complite.reset ();
                        }
                    }

                  //  Если сообщение часть транзакции, но модуль-обработчик не определен, это выглядит как ошибка. Пока просто обрабатваем такую ситуацию так.
                  if (!_src_complite && !current_seq_.dest_)
                    {
                      UASSERT_SIGNAL ("failed [!_src_complite && !current_seq_.dest_]");
                      _src_complite = _src;
                    }

                  //  Если сообщение не часть транзакции - завершаем его через источник.
                  if (_src_complite)
                    {
                      UASSERT (!_functs.empty ());
                      _src_complite->complite_msg (_last_msg, current_seq_);
                    }
                  //  Иначе,
                  //  1. Добавляем транзакцию для того сообщения, которое нам пришло изначально
                  //  2. Чистим сообщение синхронности.
                  //  3. Передаем сообщение в найденный модуль
                  else
                    {
                      UASSERT (current_seq_.dest_);
                      if (_seqs_exist)
                        {
                          IEvent::ptr _seq_msg = ::libs::events::helpers::wrap_seq_msg (_recv_msg, current_seq_.id_seq_);
                          current_seq_.dest_->send_msg (_seq_msg);
                        }
                      else
                        {
                          current_seq_.dest_->send_msg (_recv_msg);
                        }
                      //current_seq_.dest_->send_msg ( _last_msg );
                    }
                }

              //  сброс переменных вне цикла.
              {
                current_seq_.reset ();
                _functs.clear ();
              }
            }      //end for

          if (!_now_recv_msg)
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
              if (deinit ())
                {
                  break;
                }
            }
        }
      while (true);
    }
  catch (const std::exception& _e)
    {
      EXCEPT_LOG (logger_, _e.what (), text_id_module_.c_str ());
    }
  return;
}

}}}}      // namespace libs::ilink::appl::root
