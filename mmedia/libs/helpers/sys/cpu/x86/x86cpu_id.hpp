#pragma once
/**
\file       x86cpu_id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

// old shit
namespace libs::helpers::sys::cpu::x86
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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
