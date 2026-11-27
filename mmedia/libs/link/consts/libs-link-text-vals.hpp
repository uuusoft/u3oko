#pragma once
/**
\file       libs-link-text-vals.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\brief      Константы для конструирования ключей к различным частям реализации подсистемы сообщений
*/

namespace libs::link::consts::text
{
inline constexpr std::string_view id_service_name    = "libs.link.consts.text.name_service";              //< имя сервиса используется как часть пути к файлам настроек и данных для данного сервиса
inline constexpr std::string_view id_lib_name        = "libs.link.consts.text.name_lib";                  //<
inline constexpr std::string_view id_proc_name       = "libs.link.consts.text.name_proc";                 //< remove?
inline constexpr std::string_view id_company_name    = "libs.link.consts.text.name_company";              //< используется для формирования уникальных идентификаторов в разделяемом памяти
inline constexpr std::string_view id_appl_name       = "libs.link.consts.text.name_application";          //<
inline constexpr std::string_view id_name_queue2dest = "libs.link.consts.text.name_msgs_queue";           //<
inline constexpr std::string_view id_name_shared_mem = "libs.link.consts.text.name_shared_mem";           //< размер максимальный буфера для передачи сообщений при работе модулей в разлчиных процессах
inline constexpr std::string_view id_sync_init_event = "libs.link.consts.text.name_sync_init_event";      //<
inline constexpr std::string_view id_size_shared_mem = "libs.link.consts.text.name_size_shared_mem";      //<
inline constexpr std::string_view id_module_links    = "libs.link.consts.text.name_module_links";         //<
inline constexpr std::string_view id_code_runs       = "libs.link.consts.text.name_code_runs";            //< определяет каким образом dll будет загружена (в текущее адрессное простанство или в другой процесс)
inline constexpr std::string_view id_server_side     = "libs.link.consts.text.name_server_side";          //< используется для выбора очереди при передачи/приеме сообщений
inline constexpr std::string_view id_shared_mem_base = "uuusoft.prg.mmedia.libs.link.shared_mem_base.";   //<
inline constexpr std::string_view id_delay_ms        = "delay";                                           //<
}   // namespace libs::link::consts::text

namespace libs::link::consts::text::defaults
{
inline constexpr std::string_view company_name = "uuusoft";     //<
inline constexpr std::string_view appl_name    = "u3oko";       //<
inline constexpr std::string_view service_name = "service#0";   //<
}   // namespace libs::link::consts::text::defaults

#if 0
namespace libs::link::consts::text
{
extern const char* id_service_name;
extern const char* id_lib_name;
extern const char* id_proc_name;
extern const char* id_company_name;
extern const char* id_appl_name;
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
#endif
