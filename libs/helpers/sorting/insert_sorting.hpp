//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       insert_sorting.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace sorting {
/**
  \brief          Сортировка вставкой последовательности [_beg, _end), полезна для малых последовательностей.
  \tparam         TTIt  тип итератор произвольного доступа.
  \param[in, out] _beg  начало сортируемой последовательности.
  \param[in, out] _end  элемент за окончанием последовательности.
  \return         пусто
  */
template <typename TTIt>
void
sorting_inplace_insert (TTIt _beg, TTIt _end)
{
  for (TTIt _eit = std::next (_beg); _eit != _end; ++_eit)
    {
      for (TTIt _iit = _eit; _iit != _beg && (*_iit < *(std::prev (_iit))); --_iit)
        {
          std::swap (*_iit, *std::prev (_iit));
        }
    }

  UASSERT (std::is_sorted (_beg, _end));
  return;
}

}}}      // namespace libs::helpers::sorting
