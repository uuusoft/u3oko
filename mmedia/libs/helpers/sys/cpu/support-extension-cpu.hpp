#pragma once
/**
\file       support-extension-cpu.hpp
\brief      возращает описание типа процессора через инструкцию cpuid
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::sys::cpu
{
struct SupportExtensionCPU final {
  SupportExtensionCPU ()  = default;
  ~SupportExtensionCPU () = default;

  void
  reset ()
  {
    id_cpu_.clear ();
    exts_cpu_.clear ();
    minor_exts_cpu_.clear ();
  }

  bool
  check (const CpuExts& prop) const
  {
    return exts_cpu_.end () == exts_cpu_.find (prop) ? false : true;
  }

  bool
  check (const CpuMinorExts& prop) const
  {
    return minor_exts_cpu_.end () == minor_exts_cpu_.find (prop) ? false : true;
  }

  void
  set (const CpuExts& prop)
  {
    exts_cpu_.insert (prop);
  }

  void
  set (const CpuMinorExts& prop)
  {
    minor_exts_cpu_.insert (prop);
  }

  void
  clear (const CpuExts& prop)
  {
    exts_cpu_.erase (prop);
  }

  void
  clear (const CpuMinorExts& prop)
  {
    minor_exts_cpu_.erase (prop);
  }

  std::string                        id_cpu_;           //<
  std::unordered_set< CpuExts >      exts_cpu_;         //<
  std::unordered_set< CpuMinorExts > minor_exts_cpu_;   //<
};
}   // namespace libs::helpers::sys::cpu
