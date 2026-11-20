#pragma once
/**
\file       dbufs-video-const-offs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\brief      Объявление зарезервированных констант типов-индексов буфера данных
*/

namespace utils::dbufs::video::consts::offs
{
using off_buf_type            = std::string_view;   //< тип для идентификатора типа буфера
using persistent_off_buf_type = std::string;        //<

inline constexpr off_buf_type empty                  = "";
inline constexpr off_buf_type invalid                = "???";
inline constexpr off_buf_type any                    = "***";
inline constexpr off_buf_type raw                    = "raw";
inline constexpr off_buf_type hue                    = "hue";
inline constexpr off_buf_type huex2                  = "huex2";
inline constexpr off_buf_type huex4                  = "huex4";
inline constexpr off_buf_type huex8                  = "huex8";
inline constexpr off_buf_type sat                    = "sat";
inline constexpr off_buf_type satx2                  = "satx2";
inline constexpr off_buf_type satx4                  = "satx4";
inline constexpr off_buf_type satx8                  = "satx8";
inline constexpr off_buf_type lit                    = "lit";
inline constexpr off_buf_type litx2                  = "litx2";
inline constexpr off_buf_type litx4                  = "litx4";
inline constexpr off_buf_type litx8                  = "litx8";
inline constexpr off_buf_type zhsl                   = "zhsl";
inline constexpr off_buf_type http                   = "http";
inline constexpr off_buf_type storage                = "storage";
inline constexpr off_buf_type mjpg                   = "mjpg";
inline constexpr off_buf_type mpg1                   = "mpg1";
inline constexpr off_buf_type mpg2                   = "mpg2";
inline constexpr off_buf_type mpg3                   = "mpg3";
inline constexpr off_buf_type mpg4                   = "mpg4";
inline constexpr off_buf_type x264                   = "x264";
inline constexpr off_buf_type x265                   = "x265";
inline constexpr off_buf_type vp7                    = "vp7";
inline constexpr off_buf_type vp9                    = "vp9";
inline constexpr off_buf_type move_detect_diff       = "move-detect-diff";
inline constexpr off_buf_type move_detect_res        = "move-detect-res";
inline constexpr off_buf_type face_detect_res        = "face-detect-res";
inline constexpr off_buf_type space_noise_filter_res = "space-noise-filter-res";
inline constexpr off_buf_type time_noise_filter_res  = "time-noise-filter-res";
inline constexpr off_buf_type freq_noise_filter_res  = "freq-noise-filter-res";
inline constexpr off_buf_type move_est_res           = "move-est-res";
inline constexpr off_buf_type temp1                  = "tmp1";
inline constexpr off_buf_type temp2                  = "tmp2";
inline constexpr off_buf_type temp3                  = "tmp3";
}   // namespace utils::dbufs::video::consts::offs
