#pragma once
/**
\file       libs-link-text-vals.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
\brief      Константы для конструирования ключей к различным частям реализации подсистемы сообщений
*/

namespace libs::link::consts::text
{
extern const char* id_service_name;
extern const char* id_lib_name;
extern const char* id_proc_name;
extern const char* id_company_name;
extern const char* id_appl_name;
extern const char* id_subsys_name;
extern const char* id_name_queue2dest;
extern const char* id_name_shared_mem;
extern const char* id_sync_init_event;
extern const char* id_size_shared_mem;
extern const char* id_module_links;
extern const char* id_code_runs;
extern const char* id_shared_mem_base;
extern const char* id_server_side;
extern const char* id_delay_ms;
}   // namespace libs::link::consts::text

namespace libs::link::consts::text::defaults
{
extern const char* company_name;
extern const char* appl_name;
extern const char* service_name;
}   // namespace libs::link::consts::text::defaults
