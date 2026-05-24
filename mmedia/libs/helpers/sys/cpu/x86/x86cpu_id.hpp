#pragma once
/**
\file       x86cpu_id.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

// old shit
namespace libs::helpers::sys::cpu::x86
{
#if 0
inline tstring
get_id ()
{
  tstring          ret;
  low_cpu::CpuInfo helper;

  helper.full_text (ret);
  U3_ASSERT (!ret.empty ());
  return ret;
}


inline tstring
get_speed ()
{
  return tstring (_T("???"));
}
#endif
}   // namespace libs::helpers::sys::cpu::x86
