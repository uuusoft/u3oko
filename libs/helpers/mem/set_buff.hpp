#pragma once
/**
\file       set_buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace mem {
/*
  \brief  empty brief
  */
template <
  typename TTSource>
void
set_buff (TTSource* _src, TTSource _val, std::size_t _count)
{
  UASSERT (_src);
  UASSERT (_count > 0);
  std::fill (_src, _src + _count, _val);
  return;
}

}}}      // namespace libs::helpers::mem
