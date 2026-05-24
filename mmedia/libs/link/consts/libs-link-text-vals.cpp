/**
\file       libs-link-text-vals.cpp
\date       07.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
\brief      Константы для конструирования ключей к различным частям реализации подсистемы сообщений
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-link-includes_int.hpp"
#include "libs-link-text-vals.hpp"

namespace libs::link::consts::text
{
const char* id_service_name      = "libs.link.consts.text.name_service";
const char* id_lib_name          = "libs.link.consts.text.name_lib";
const char* id_proc_name         = "libs.link.consts.text.name_proc";
const char* id_company_name      = "libs.link.consts.text.name_company";
const char* id_appl_name         = "libs.link.consts.text.name_application";
const char* id_subsys_name       = "libs.link.consts.text.name_subsys";
const char* id_name_queue2dest   = "libs.link.consts.text.name_msgs_queue";
const char* id_name_shared_mem   = "libs.link.consts.text.name_shared_mem";
const char* id_sync_init_event   = "libs.link.consts.text.name_sync_init_event";
const char* id_shared_mem_base   = "uuusoft.prg.mmedia.libs.link.shared_mem_base.";
const char* id_delay_ms          = "delay";
const char* default_company_name = "uuusoft";
const char* default_appl_name    = "u3oko";
const char* default_service_name = "service#0";
}   // namespace libs::link::consts::text
