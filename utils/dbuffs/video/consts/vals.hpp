#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление констант геометрии буфера под видео.
*/

namespace utils { namespace dbuffs { namespace video { namespace consts {

const int min_width  = 160;              //< Минимальная ширина буфера в точках.
const int min_height = 120;              //< Минимальная высота буфера в точках.
const int max_width  = 8 * 32 * 32;      //< Максимальная ширина буфера в точках.
const int max_height = 8 * 32 * 32;      //< Максимальная высота буфере в точках.

}}}}      // namespace utils::dbuffs::video::consts
