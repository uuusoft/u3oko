#pragma once
/**
\file       dbufs-video-const-offs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
\brief      Объявление зарезервированных констант типов-индексов буфера данных.
*/

namespace utils::dbufs::video::consts::offs
{
using off_buf_type = std::string;   //< тип для идентификатора типа буфера

extern const off_buf_type empty;                    //< Идентификатор недействительного буфера
extern const off_buf_type invalid;                  //< Идентификатор недействительного буфера
extern const off_buf_type any;                      //< Идентификатор произвольного буфера
extern const off_buf_type raw;                      //< Буфер с несжатыми, сырыми данными (т.е данными, принятыми от устройства в стандартном формате RGB24, YUY2, Y8, etc)
extern const off_buf_type hue;                      //< Буфер компоненты hue
extern const off_buf_type huex2;                    //< Буфер компоненты hue c прореживанием 2
extern const off_buf_type huex4;                    //< Буфер компоненты hue c прореживанием 4
extern const off_buf_type huex8;                    //< Буфер компоненты hue c прореживанием 8
extern const off_buf_type sat;                      //< Буфер компоненты saturaton
extern const off_buf_type satx2;                    //< Буфер компоненты saturaton c прореживанием 2
extern const off_buf_type satx4;                    //< Буфер компоненты saturaton c прореживанием 4
extern const off_buf_type satx8;                    //< Буфер компоненты saturaton c прореживанием 8
extern const off_buf_type lit;                      //< Буфер компоненты lightness
extern const off_buf_type litx2;                    //< Буфер компоненты lightness c прореживанием 2
extern const off_buf_type litx4;                    //< Буфер компоненты lightness c прореживанием 4
extern const off_buf_type litx8;                    //< Буфер компоненты lightness c прореживанием 8
extern const off_buf_type zhsl;                     //< Буфер сжатого кадра в пространстве HSL Внутренний формат
extern const off_buf_type http;                     //< Буфер сжатого кадра внешним кодеком MJPEG
extern const off_buf_type storage;                  //< Буфер для системы хранения данных
extern const off_buf_type mjpg;                     //< Буфер сжатого кадра внешним кодеком MJPEG
extern const off_buf_type mpg1;                     //< Буфер сжатого кадра внешним кодеком MJPG1
extern const off_buf_type mpg2;                     //< Буфер сжатого кадра внешним кодеком MJPG2
extern const off_buf_type mpg3;                     //< Буфер сжатого кадра внешним кодеком MJPG3
extern const off_buf_type mpg4;                     //< Буфер сжатого кадра внешним кодеком MJPG4
extern const off_buf_type x264;                     //< Буфер сжатого кадра внешним кодеком x264
extern const off_buf_type x265;                     //< Буфер сжатого кадра внешним кодеком x265
extern const off_buf_type vp7;                      //< Буфер сжатого кадра внешним кодеком vp7
extern const off_buf_type vp9;                      //< Буфер сжатого кадра внешним кодеком vp9
extern const off_buf_type move_detect_diff;         //< Результат работы детектора движения
extern const off_buf_type move_detect_res;          //< Результат работы детектора движения
extern const off_buf_type face_detect_res;          //< Результат работы детектора лица
extern const off_buf_type space_noise_filter_res;   //< Результат работы
extern const off_buf_type time_noise_filter_res;    //< Результат работы
extern const off_buf_type freq_noise_filter_res;    //< Результат работы
extern const off_buf_type move_est_res;             //< Результат работы
extern const off_buf_type temp1;                    //< Временный буфер 1
extern const off_buf_type temp2;                    //< Временный буфер 2
extern const off_buf_type temp3;                    //< Временный буфер 3
}   // namespace utils::dbufs::video::consts::offs
