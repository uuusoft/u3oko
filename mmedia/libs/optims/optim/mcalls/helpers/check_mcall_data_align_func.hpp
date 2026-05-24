#pragma once
/**
\file       check_mcall_data_align_func.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_lib
*/

namespace libs::optim::mcalls::helpers
{
/// Вспомогательная функция проверки значения выравнивания данных на корректность
/// \param[in]  align  проверямое значение выравнивания данных
/// \return     true, если значение корректно
inline bool
check_mcall_data_align (const std::uint32_t align)
{
  if (1 != align && 2 != align && 8 != align && 16 != align && 32 != align && 64 != align)
  {
    U3_XLOG_ERROR ("align value: " + VTOLOG (align));
    return false;
  }
  return true;
}
}   // namespace libs::optim::mcalls::helpers
