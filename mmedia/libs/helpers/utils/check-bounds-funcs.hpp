#pragma once
/**
\file       check-bounds-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::utils
{
/// Функция проверки значения формата плавающей точки одинарной точности на вырожденность
inline void
check_float (float* val, float def_val = 0.0F)
{
  U3_ASSERT (val);
  const bool res = std::isnormal (*val);
  //  if its SNAN, QNAN or denorm reset to 0.0F
  if (!res)
  {
    U3_ASSERT_SIGNAL ("failed");
    *val = def_val;
  }
}

/// Функция безопасной коррекции значения в заданный диапазон
template< typename TTVal >
void
check_bound (TTVal& val, const TTVal& min, const TTVal& max)
{
  val = std::max< TTVal > (min, val);
  val = std::min< TTVal > (max, val);
}

/// Функция безпоасной коррекции значения в диапазон
template< typename TTVal >
TTVal
ret_check_bound (const TTVal& val, const TTVal& min, const TTVal& max)
{
  TTVal ret = val;
  check_bound (ret, min, max);
  return ret;
}
}   // namespace libs::helpers::utils
