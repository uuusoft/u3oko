#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace consts {

#if defined(UUU_DEBUG)
const int send_msg_max_wait_ms = 10 * 60 * 1000;
#else
const int send_msg_max_wait_ms = 1 * 60 * 1000;
#endif

const int received_msg_max_wait_ms = 1;              //< ???
const int max_count_msgs           = 128;            //< Максимальное количество сообщений в очередях передачи.
const int max_size_msg             = 32 * 1024;      //< Максимальный размер сообщения в байтах.

#if defined(UUU_OS_WIN32_DESKTOP) || defined(UUU_OS_GNU_LINUX)

const int size_shared_mem_bytes  = 4 * 4 * 1024 * 1024 * 4;
const int wait_delay_recv_msg_ms = 5;

#elif defined(UUU_OS_RASPBERRY)

const int size_shared_mem_bytes  = 5 * 1024 * 1024;
const int wait_delay_recv_msg_ms = 5;

#elif defined(UUU_OS_ANDROID)

const int size_shared_mem_bytes  = 50 * 1024 * 1024;
const int wait_delay_recv_msg_ms = 5;

#else
#error failed select OS
#endif

}}}      // namespace libs::link::consts
