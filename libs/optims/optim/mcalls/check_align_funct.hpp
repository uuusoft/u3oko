//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       check_align_funct.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace mcalls {
/**
\brief      Вспомогательная функция проверки значения выравнивания данных на корректность.
\param[in]  _align  проверямое значение выравнивания данных
\return     true, если значение корректно.
*/
inline bool
check_align (const std::size_t _align)
{
  if (1 != _align && 8 != _align && 16 != _align && 32 != _align && 64 != _align)
    {
      XULOG_ERROR ("failed aling, " << _align);
      return false;
    }
  return true;
}

}}}      // namespace libs::optim::mcalls
