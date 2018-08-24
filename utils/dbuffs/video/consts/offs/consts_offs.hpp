#pragma once
/**
\file       consts_offs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление зарезериврированных констант типов-индексов буфера данных.
*/

namespace utils { namespace dbuffs { namespace video { namespace consts { namespace offs {

using off_buff_type = std::string;      //< тип для идентификатора типа буфера.

const off_buff_type empty   = "";          //< Идентификатор недействительного буфера.
const off_buff_type invalid = "???";       //< Идентификатор недействительного буфера.
const off_buff_type any     = "***";       //< Идентификатор произвольного буфера.
const off_buff_type raw     = "raw";       //< Буфер с несжатыми, сырыми данными (т.е. данными, принятыми от устройства в стандартном формате RGB24, YUY2, Y8, etc).
const off_buff_type hue     = "hue";       //< Буфер компоненты hue.
const off_buff_type sat     = "sat";       //< Буфер компоненты saturaton.
const off_buff_type lit     = "lit";       //< Буфер компоненты lightness.
const off_buff_type zhsl    = "zhsl";      //< Буфер сжатого кадра в пространстве HSL. Внутренний формат.
const off_buff_type mjpg    = "mjpg";      //< Буфер сжатого кадра внешним кодеком MJPEG.
const off_buff_type mpg1    = "mpg1";      //< Буфер сжатого кадра внешним кодеком MJPG1.
const off_buff_type mpg2    = "mpg2";      //< Буфер сжатого кадра внешним кодеком MJPG2.
const off_buff_type mpg3    = "mpg3";      //< Буфер сжатого кадра внешним кодеком MJPG3.
const off_buff_type mpg4    = "mpg4";      //< Буфер сжатого кадра внешним кодеком MJPG4.
const off_buff_type x264    = "x264";      //< Буфер сжатого кадра внешним кодеком x264.
const off_buff_type x265    = "x265";      //< Буфер сжатого кадра внешним кодеком x265.
const off_buff_type vp7     = "vp7";       //< Буфер сжатого кадра внешним кодеком vp7.
const off_buff_type vp9     = "vp9";       //< Буфер сжатого кадра внешним кодеком vp9.
const off_buff_type temp1   = "tmp1";      //< Временный буфер 1.
const off_buff_type temp2   = "tmp2";      //< Временный буфер 2.
const off_buff_type temp3   = "tmp3";      //< Временный буфер 3.
const off_buff_type temp4   = "tmp4";      //< Временный буфер 4.
const off_buff_type temp5   = "tmp5";      //< Временный буфер 5.

}}}}}      // namespace utils::dbuffs::video::consts::offs
