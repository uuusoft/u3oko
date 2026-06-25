/**
\file       cpu-info.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../helpers-lib-includes_int.hpp"
#include "x86/x86_cpu.hpp"
#include "arm/arm_cpu.hpp"

namespace libs::helpers::sys::cpu
{
CpuInfo::CpuInfo ()
{
  ext_minor_cpu_ranged_.reserve (32);
  ext_cpu_ranged_.reserve (32);
  ext_dsp_ranged_.reserve (32);

  ext_dsp_ranged_.push_back (DspExts::hexagon6);
  ext_dsp_ranged_.push_back (DspExts::hexagon5);
  ext_dsp_ranged_.push_back (DspExts::hexagon4);

  ext_cpu_ranged_.push_back (CpuExts::neon);
  ext_cpu_ranged_.push_back (CpuExts::avx2);
  ext_cpu_ranged_.push_back (CpuExts::avx1);
  ext_cpu_ranged_.push_back (CpuExts::sse4_2);
  ext_cpu_ranged_.push_back (CpuExts::sse4_1);
  ext_cpu_ranged_.push_back (CpuExts::sse3);
  ext_cpu_ranged_.push_back (CpuExts::sse2);

  ext_minor_cpu_ranged_.push_back (CpuMinorExts::fma);
  ext_minor_cpu_ranged_.push_back (CpuMinorExts::f16c);
  ext_minor_cpu_ranged_.push_back (CpuMinorExts::rdrand);

  // ext_cpu_ranged_.push_back(CpuExts::sse1 );
  // ext_cpu_ranged_.push_back(CpuExts::mmx);

  all_ext_.reserve (128);

  std::copy (ext_cpu_ranged_.rbegin (), ext_cpu_ranged_.rend (), back_inserter (all_ext_));

  // all_ext_.push_back (CpuExts::f16c);
  // all_ext_.push_back (CpuExts::rdrand);

#ifdef U3_CPU_X86
  U3_CHECK (x86::get_all_info_cpu (exts_), "get info cpu");
#elif defined(U3_CPU_ARM)
  U3_CHECK (arm::get_all_info_cpu (exts_), "failde get info cpu");
#else
#  error "unknow cpu"
#endif
}


CpuExts
CpuInfo::get_max () const
{
  for (const CpuExts& ext : ext_cpu_ranged_)
  {
    if (exts_.check (ext))
    {
      return ext;
    }
  }
  return CpuExts::usual;
}


CpuExts
CpuInfo::get_min () const
{
  CpuExts ret = CpuExts::usual;
  for (const CpuExts& ext : ext_cpu_ranged_)
  {
    if (exts_.check (ext))
    {
      ret = ext;
    }
  }
  return ret;
}


bool
CpuInfo::is_less (const CpuExts& op1, const CpuExts& op2) const
{
  for (const CpuExts& ext : ext_cpu_ranged_)
  {
    if (ext == op1)
    {
      return false;
    }
    if (ext == op2)
    {
      return true;
    }
  }

  U3_ASSERT_SIGNAL_NT ("failed");
  return false;
}


void
CpuInfo::full_text (std::string& info)
{
  info.reserve (512);

  info = "cpu ";

#ifdef U3_CPU_X86
  info += x86::get_text_about_cpu ();
#elif defined(U3_CPU_ARM)
  info += arm::get_text_about_cpu ();
#else
#  error
#endif

  info += "\n";
  info += "ext: ";

  for (const CpuExts& ext : all_ext_)
  {
    if (!exts_.check (ext))
    {
      continue;
    }

    info += texter_.get_text (ext);
    info += " ";
  }
}
}   // namespace libs::helpers::sys::cpu
