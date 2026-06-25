#pragma once
/**
\file       module-http-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mhttp
*/

namespace modules::mhttp::appl::consts
{
constexpr std::uint32_t count_work_threads                   = 4;                               //<
constexpr std::uint32_t port                                 = 8081;                            //<
constexpr std::uint32_t ssl_port                             = 8082;                            //<
constexpr std::int32_t expires_after                         = 60;                              //<
constexpr std::int32_t body_limit                            = 5 * 1024 * 1024;                 //< 5 MB
constexpr std::size_t requests_queue_limit                   = 8;                               //<
constexpr std::int64_t max_size_sending_data                 = 10 * 1024 * 1024;                //< 10 MB
constexpr std::chrono::seconds inform_period_about_skip_data = std::chrono::seconds (5 * 60);   //< 5 min

extern const std::string module_name;        //<
extern const std::string temp_folder_name;   //<
extern const char*       id_zip_buf2http;    //< Идентификатор ресурса (jpeg изображение) для http
extern const char*       index_html_id;      //<
}   // namespace modules::mhttp::appl::consts
