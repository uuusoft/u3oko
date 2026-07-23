/**
\file       libs-link-text-vals.cpp
\date       07.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
\brief      Константы для конструирования ключей к различным частям реализации подсистемы сообщений
*/
#include "../_make/libs-link-includes_int.hpp"
#include "libs-link-text-vals.hpp"

namespace libs::link::consts::text
{
const char* id_service_name    = "libs.link.consts.text.name_service";              //< имя сервиса используется как часть пути к файлам настроек и данных для данного сервиса
const char* id_lib_name        = "libs.link.consts.text.name_lib";                  //<
const char* id_proc_name       = "libs.link.consts.text.name_proc";                 //< remove?
const char* id_company_name    = "libs.link.consts.text.name_company";              //< используется для формирования уникальных идентификаторов в разделяемом памяти
const char* id_appl_name       = "libs.link.consts.text.name_application";          //<
const char* id_name_queue2dest = "libs.link.consts.text.name_msgs_queue";           //<
const char* id_name_shared_mem = "libs.link.consts.text.name_shared_mem";           //< размер максимальный буфера для передачи сообщений при работе модулей в разлчиных процессах
const char* id_sync_init_event = "libs.link.consts.text.name_sync_init_event";      //<
const char* id_size_shared_mem = "libs.link.consts.text.name_size_shared_mem";      //<
const char* id_module_links    = "libs.link.consts.text.name_module_links";         //<
const char* id_code_runs       = "libs.link.consts.text.name_code_runs";            //< определяет каким образом dll будет загружена (в текущее адрессное простанство или в другой процесс)
const char* id_server_side     = "libs.link.consts.text.name_server_side";          //< используется для выбора очереди при передачи/приеме сообщений
const char* id_shared_mem_base = "uuusoft.prg.mmedia.libs.link.shared_mem_base.";   //<
const char* id_delay_ms        = "delay";                                           //<
// const char* id_subsys_name     = "libs.link.consts.text.name_subsys";               //<
}   // namespace libs::link::consts::text

namespace libs::link::consts::text::defaults
{
const char* company_name = "uuusoft";     //<
const char* appl_name    = "u3oko";       //<
const char* service_name = "service#0";   //<
}   // namespace libs::link::consts::text::defaults
