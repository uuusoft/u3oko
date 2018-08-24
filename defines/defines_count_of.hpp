//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_count_of.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Определение макроса для подсчета количества элементов в массиве.
*/
namespace defines {

template <int N>
struct chars_size_equal_n
{
  unsigned char vals_[N];
};


template <typename C, int N>
chars_size_equal_n<N>& make_chars_size_equal_n (C (&)[N]);
}      // namespace defines

#ifndef COUNT_OF
//  Первый вариант, основа взята из boost что ли, не помню.
//#define COUNT_OF(MARRAY) ((sizeof (MARRAY) / sizeof (0 [MARRAY])) / ((std::size_t) (!(sizeof (MARRAY) % sizeof (0 [MARRAY])))))
#endif

#ifndef COUNT_OF
//  Второй вариант вычисления размера массива, см. "Расширение библиотеки STL для C++", 5.1.2
#define COUNT_OF(MARRAY) (sizeof (defines::make_chars_size_equal_n (MARRAY)))
#endif
