//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       leaf-module-work-funct.cpp
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

void
LeafModule::work_int ()
{
  try
    {
      recv_links_type           _srss = get_recv_link ();
      list_catch_msg_funct_type _functs;

      do
        {
          bool _recv_msg = false;
          for (auto& _src : _srss)
            {
              auto _msg = _src ? _src->received_msg () : IEvent::ptr ();
              if (!_msg)
                {
                  XULOG_TRACE ("LeafModule::work_int, received null msg, skip, " << text_id_module_);
                  continue;
                }

              _recv_msg      = true;
              auto _last_msg = _msg;
              XULOG_TRACE ("LeafModule::work_int, received msg, " << _msg->get_mid () << ", " << text_id_module_);
              //  Прямая сборка стека функций для обработки данного сообщения.
              //  Формируем описание запроса (все флаги, транзакцию и прочее).
              while (_msg)
                {
                  std::pair<IEvent::raw_ptr, IEvent::hid_type> _cmsgs[] = {
                    { _msg.get (), _msg->get_mid () },
                    { ::libs::iproperties::helpers::cast_event<ievents::runtime::RuntimeEvent> (_msg), ievents::runtime::RuntimeEvent::gen_get_mid () },
                    { ::libs::iproperties::helpers::cast_event<::libs::ilog_events::events::InfoLogEvent> (_msg), ::libs::ilog_events::events::InfoLogEvent::gen_get_mid () }
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

                  catch_msg_funct_type _funct = std::bind (&LeafModule::default_catch_funct, this, std::placeholders::_1, std::placeholders::_2);
                  if (catch_functs_.end () != _find)
                    {
                      _funct = _find->second;
                    }

                  _functs.push_back (std::make_pair (_funct, _msg));
                  _msg      = _funct (_msg, true);
                  _last_msg = _msg ? _msg : _last_msg;
                }

              XULOG_TRACE (text_id_module_ << ", leaf: msg received, " << helpers::to_str (current_seq_) << ", " << _last_msg->get_mid ());
              if (!catch_event (_last_msg))
                {
                  //UUU_THROW_INFO_EXCEPTION( "subsys exit" );
                }

              UASSERT (!_functs.empty ());
              auto _src_complite = _src;
              //  Если конечному модулю пришел ответ, ненадо пересылать его дальше. Ответа на ответ не существует.
              //  Если это и не был запрос (а установка), опять же ничего пересылать не надо.
              if (!current_seq_.answer_ && current_seq_.request_)
                {
                  _src->complite_msg (_last_msg, current_seq_);
                }
              //  Если сообщение не часть транзакции - завершаем его через источник.
              if (!current_seq_.is_seq_exist ())
                {
                  _functs.clear ();
                  _src_complite->complite_msg (_last_msg, current_seq_);
                }
              //  сброс переменных вне цикла.
              current_seq_.reset ();
              _functs.clear ();
            }      //for

          if (is_now_sleep_thread (_recv_msg))
            {
              std::this_thread::sleep_for (std::chrono::milliseconds (ms_time_sleep_));
            }

          if (stop_module_)
            {
              break;
            }
        }
      while (true);
    }
  catch (const std::exception& _e)
    {
      EXCEPT_LOG (logger_, _e.what (), text_id_module_.c_str ());
    }
  deinit ();
  return;
}

}}}}      // namespace libs::ilink::appl::leaf
