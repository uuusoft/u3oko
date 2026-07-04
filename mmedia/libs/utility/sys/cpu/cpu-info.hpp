#pragma once
/**
\file       cpu-info.hpp
\brief      Class for checking CPU
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
class CpuInfo final
{
  public:
  CpuInfo ();

  CpuExts get_max () const;
  CpuExts get_min () const;

  bool is_less (const CpuExts& op1, const CpuExts& op2) const;
  void full_text (std::string& info);

  protected:
  SupportExtensionCPU         exts_;                   //<
  TextExtCpu                  texter_;                 //<
  std::vector< CpuExts >      ext_cpu_ranged_;         //<
  std::vector< CpuMinorExts > ext_minor_cpu_ranged_;   //<
  std::vector< DspExts >      ext_dsp_ranged_;         //<
  std::vector< CpuExts >      all_ext_;                //<
};
}   // namespace libs::utility::sys::cpu
