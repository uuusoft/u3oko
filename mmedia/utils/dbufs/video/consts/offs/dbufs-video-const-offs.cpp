/**
\file       dbufs-video-const-offs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_dbufs
\brief      Объявление зарезервированных констант типов-индексов буфера данных
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

namespace utils::dbufs::video::consts::offs
{
const off_buf_type empty                  = "";
const off_buf_type invalid                = "???";
const off_buf_type any                    = "***";
const off_buf_type raw                    = "raw";
const off_buf_type hue                    = "hue";
const off_buf_type huex2                  = "huex2";
const off_buf_type huex4                  = "huex4";
const off_buf_type huex8                  = "huex8";
const off_buf_type sat                    = "sat";
const off_buf_type satx2                  = "satx2";
const off_buf_type satx4                  = "satx4";
const off_buf_type satx8                  = "satx8";
const off_buf_type lit                    = "lit";
const off_buf_type litx2                  = "litx2";
const off_buf_type litx4                  = "litx4";
const off_buf_type litx8                  = "litx8";
const off_buf_type zhsl                   = "zhsl";
const off_buf_type http                   = "http";
const off_buf_type storage                = "storage";
const off_buf_type mjpg                   = "mjpg";
const off_buf_type mpg1                   = "mpg1";
const off_buf_type mpg2                   = "mpg2";
const off_buf_type mpg3                   = "mpg3";
const off_buf_type mpg4                   = "mpg4";
const off_buf_type x264                   = "x264";
const off_buf_type x265                   = "x265";
const off_buf_type vp7                    = "vp7";
const off_buf_type vp9                    = "vp9";
const off_buf_type move_detect_diff       = "move-detect-diff";
const off_buf_type move_detect_res        = "move-detect-res";
const off_buf_type face_detect_res        = "face-detect-res";
const off_buf_type space_noise_filter_res = "space-noise-filter-res";
const off_buf_type time_noise_filter_res  = "time-noise-filter-res";
const off_buf_type freq_noise_filter_res  = "freq-noise-filter-res";
const off_buf_type move_est_res           = "move-est-res";
const off_buf_type temp1                  = "tmp1";
const off_buf_type temp2                  = "tmp2";
const off_buf_type temp3                  = "tmp3";
}   // namespace utils::dbufs::video::consts::offs
