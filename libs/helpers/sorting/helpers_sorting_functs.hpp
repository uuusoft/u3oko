//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       helpers_sorting_functs.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace sorting {
/**
  \brief          Вспомогательная функция обмена по условию "больше".
  \tparam         TTVal тип обмениваемого значения.
  \param[in, out] _val1 .
  \param[in, out] _val2 .
  \return         пусто
  */
template <typename TTVal>
void
swap_if_large (TTVal& _val1, TTVal& _val2)
{
  if (_val1 > _val2)
    {
      std::swap (_val1, _val2);
    }
  return;
}

}}}      // namespace libs::helpers::sorting
