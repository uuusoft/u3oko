#pragma once
/**
\file       type-stage-de-init.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.07.2018
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace appl { namespace root {
/**
  \brief  Стадии отключения основого модуля.
  */
enum struct TypeStageDeInit
{
  send_stop_msg2allmost_all = 0,      //< Первая стадия - посылка сообщений СТОП всем модулям (исключая основной  модуль логирования).
  wait_stop_data_module     = 1,      //< Ожидание остановки модуля обработки данных.
  wait_stop_gui_module      = 2,      //< Ожидание остановки модуля GUI.
  wait_stop_rtp_module      = 3,      //< Ожидание остановки модуля ???.
  wait_stop_storage_module  = 4,      //< Ожидание остановки модуля ???.
  wait_stop_events_module   = 5,      //< Ожидание остановки модуля событий.
  send_stop_msg2log_module  = 6,      //< Посылка сообщения СТОП модулю логирования.
  wait_stop_log_module      = 7,      //< Ожидание остановки модуля логирования.
  wait_stop_http_module     = 8,      //< Ожидание остановки модуля HTTP сервера.
  done                      = 9       //< Окончание ожидания.
};

}}}}      // namespace libs::ilink::appl::root
