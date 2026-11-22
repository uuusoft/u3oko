#pragma once
/**
\file       module-http-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace modules::mhttp::appl::consts
{
inline constexpr std::uint32_t        count_work_threads { 1 };                                   //<
inline constexpr std::uint32_t        port { 8081 };                                              //<
inline constexpr std::uint32_t        ssl_port { 8082 };                                          //<
inline constexpr std::int32_t         expires_after { 60 };                                       //< 60 sec
inline constexpr std::int32_t         body_limit { 5 * 1024 * 1024 };                             //< 5 MB
inline constexpr std::int64_t         max_size_sending_data { 10 * 1024 * 1024 };                 //< 10 MB
inline constexpr std::size_t          requests_queue_limit { 8 };                                 //<
inline constexpr std::chrono::seconds skip_data_timeout_info { std::chrono::seconds (5 * 60) };   //< 5 min
inline constexpr std::string_view     index_html_id { "index.html" };                             //<
inline constexpr std::string_view     module_name { "u3m_http" };                                 //<
inline constexpr std::string_view     temp_folder_name { "http_rw" };                             //<
}   // namespace modules::mhttp::appl::consts
