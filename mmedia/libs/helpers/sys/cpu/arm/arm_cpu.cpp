/**
\file       arm_cpu.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../helpers-lib-includes_int.hpp"
#include "arm_cpu.hpp"

#ifdef U3_CPU_ARM

namespace libs::helpers::sys::cpu::arm
{
std::string
get_text_about_cpu ()
{
  // debug
  std::string ret = "test text cpu arm";
  U3_ASSERT (!ret.empty ());
  return ret;
}


bool
get_exts_cpu (SupportExtensionCPU &ret)
{
  ret.set (CpuExts::neon);
  return true;
}


bool
get_all_info_cpu (SupportExtensionCPU &ret)
{
  ret.reset ();
  U3_CHECK_NT (get_exts_cpu (ret), "get_all_info_cpu");
  ret.id_cpu_ = get_text_about_cpu ();
  return true;
}
}   // namespace libs::helpers::sys::cpu::arm

#endif
