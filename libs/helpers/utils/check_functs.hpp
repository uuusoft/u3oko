#pragma once
/**
\file       check_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace utils {
/**
  \brief  Функция проверки значения формата плавающей точки одинарной точности на вырожденность.
  */
inline void
check_float (float* _val, float _def_val = 0.0f)
{
  UASSERT (_val);
  const bool _res = std::isnormal (*_val);
  //  if its SNAN, QNAN or denorm reset to 0.0f
  if (!_res)
    {
      UASSERT_SIGNAL ("failed");
      *_val = _def_val;
    }

  return;
}
/**
  \brief  Функция безопасной коррекции значения в заданный диапазон.
  */
template <
  typename TTVal>
void
check_bound (TTVal& _val, const TTVal& _min, const TTVal& _max)
{
  _val = std::max<TTVal> (_min, _val);
  _val = std::min<TTVal> (_max, _val);
  return;
}
/**
  \brief  Функция безпоасной коррекции значения в диапазон
  */
template <
  typename TTVal>
TTVal
ret_check_bound (const TTVal& _val, const TTVal& _min, const TTVal& _max)
{
  TTVal _ret = _val;
  check_bound (_ret, _min, _max);
  return _ret;
}

}}}      // namespace libs::helpers::utils
