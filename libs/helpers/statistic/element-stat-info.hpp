//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       element-stat-info.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace statistic {
/**
  \brief  Структура для времен одного сеанса статистики.
  */
struct ElementStatInfo
{
  ElementStatInfo () :
    min_ (count_time_type (0)),
    max_ (count_time_type (0)),
    sum_ (count_time_type (0)),
    count_ (0)
  {}

  ~ElementStatInfo ()
  {}

  duration_type min_;        //< минимальное время.
  duration_type max_;        //< максимальное время.
  duration_type sum_;        //< сумма всех времен.
  long long     count_;      //< размер суммы времен.
};

}}}      // namespace libs::helpers::statistic
