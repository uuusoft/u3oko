#pragma once
/**
\file       libs-ilink-const-vals.hpp
\date       17.07.2018
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::ilink::consts
{
using persisent_id_link_type = std::string;
using id_link_type           = std::string_view;

#if 0
// EAI-REFACT
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
#endif

inline constexpr id_link_type id_any     = "";
inline constexpr id_link_type id_appl    = "u3m_appl";
inline constexpr id_link_type id_http    = "u3m_http";
inline constexpr id_link_type id_gui     = "u3m_gui";
inline constexpr id_link_type id_storage = "u3m_store";
inline constexpr id_link_type id_rtp     = "u3m_rtp";
inline constexpr id_link_type id_events  = "u3m_events";
inline constexpr id_link_type id_log     = "u3m_log";
inline constexpr id_link_type id_data    = "u3m_data";
inline constexpr id_link_type id_ai      = "u3m_ai";
inline constexpr id_link_type id_users   = "u3m_users";
inline constexpr id_link_type id_net     = "u3m_net";
inline constexpr id_link_type id_u3oko   = "u3a_oko";
inline constexpr id_link_type id_yduff   = "u3a_yduff";
inline constexpr id_link_type id_bench   = "u3a_bench";
inline constexpr id_link_type id_u3ipcam = "u3a_ipcam";
inline constexpr id_link_type id_u3drv   = "u3a_drv";
inline constexpr id_link_type id_u3watch = "u3a_watch";
inline constexpr id_link_type id_u3mask  = "u3a_mask";

inline constexpr id_link_type id_appl_log    = "u3m_appl              ";
inline constexpr id_link_type id_http_log    = "u3m_http              ";
inline constexpr id_link_type id_gui_log     = "u3m_gui               ";
inline constexpr id_link_type id_storage_log = "u3m_store             ";
inline constexpr id_link_type id_rtp_log     = "u3m_rtp               ";
inline constexpr id_link_type id_events_log  = "u3m_events            ";
inline constexpr id_link_type id_log_log     = "u3m_log               ";
inline constexpr id_link_type id_data_log    = "u3m_data              ";
inline constexpr id_link_type id_ai_log      = "u3m_ai                ";
inline constexpr id_link_type id_users_log   = "u3m_users             ";
inline constexpr id_link_type id_net_log     = "u3m_net               ";
inline constexpr id_link_type id_u3oko_log   = "u3a_oko               ";

inline constexpr id_link_type id_module_dll_mevents  = "mpl_mevents";
inline constexpr id_link_type id_module_dll_mdata    = "mpl_mdata";
inline constexpr id_link_type id_module_dll_mai      = "mpl_mai";
inline constexpr id_link_type id_module_dll_mappl    = "mpl_mappl";
inline constexpr id_link_type id_module_dll_mhttp    = "mpl_mhttp";
inline constexpr id_link_type id_module_dll_mgui     = "mpl_mgui";
inline constexpr id_link_type id_module_dll_mlog     = "mpl_mlog";
inline constexpr id_link_type id_module_dll_mnet     = "mpl_mnet";
inline constexpr id_link_type id_module_dll_mstorage = "mpl_mstorage";
inline constexpr id_link_type id_module_dll_mtest    = "mpl_mtest";
inline constexpr id_link_type id_module_dll_musers   = "mpl_musers";

inline constexpr std::uint32_t max_count_unsend_msg { 16 * 1024 };      //<
inline constexpr std::uint32_t warning_count_unsend_msg { 1 * 1024 };   //<
}   // namespace libs::ilink::consts
