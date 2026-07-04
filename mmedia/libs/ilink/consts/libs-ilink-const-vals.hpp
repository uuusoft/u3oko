#pragma once
/**
\file       libs-ilink-const-vals.hpp
\date       17.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::consts
{
using id_link_type = std::string;

extern const char* id_any;
extern const char* id_appl;
extern const char* id_appl_log;
extern const char* id_http;
extern const char* id_http_log;
extern const char* id_gui;
extern const char* id_gui_log;
extern const char* id_storage;
extern const char* id_storage_log;
extern const char* id_rtp;
extern const char* id_rtp_log;
extern const char* id_events;
extern const char* id_events_log;
extern const char* id_log;
extern const char* id_log_log;
extern const char* id_data;
extern const char* id_data_log;
extern const char* id_ai;
extern const char* id_ai_log;
extern const char* id_users;
extern const char* id_users_log;
extern const char* id_net;
extern const char* id_net_log;

extern const char* id_u3oko;
extern const char* id_u3oko_log;
extern const char* id_yduff;
extern const char* id_bench;
extern const char* id_u3ipcam;
extern const char* id_u3drv;
extern const char* id_u3watch;
extern const char* id_u3mask;

inline constexpr std::uint32_t max_count_unsend_msg     = 16 * 1024;   //<
inline constexpr std::uint32_t warning_count_unsend_msg = 1 * 1024;    //<
}   // namespace libs::ilink::consts
