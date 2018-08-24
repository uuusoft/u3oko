//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-sub-sample.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       30.07.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief.
*/

namespace utils { namespace dbuffs { namespace video {
/**
  \brief  Перечсление возможных способов организации хранения цветовой составляющей сырых форматов видеоданных.
  */
enum struct TypeSubSample
{
  full_444 = 0,      //< Полный формат. Аналог YUV444
  sub_422  = 1,      //< Аналог YUV422
  sub_420  = 2,      //< Аналог YUV420
  sub_440  = 3,      //< Аналог YUV440
  sub_441  = 4       //< Аналог YUV441
};

}}}      // namespace utils::dbuffs::video
