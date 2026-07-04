/*
\file       text-minor-ext-cpu.cpp
\date       02.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../../utility-lib-includes_int.hpp"
#include "text-ext-dsp.hpp"

namespace libs::utility::sys::cpu
{
TextMinorExtCpu::TextMinorExtCpu ()
{
  static const std::string txts[] = {
    "fma", "f16c", "rdrand"
  };

  static const CpuMinorExts exts[] = {
    CpuMinorExts::fma, CpuMinorExts::f16c, CpuMinorExts::rdrand
  };

  for (std::size_t indx = 0; indx < std::size (txts); ++indx)
  {
    txt2val_.insert (std::pair< std::string, CpuMinorExts > (txts[indx], exts[indx]));
    val2txt_.insert (std::pair< CpuMinorExts, std::string > (exts[indx], txts[indx]));
  }
}


auto
TextMinorExtCpu::get_text (const CpuMinorExts& val) const -> std::string
{
  auto it = val2txt_.find (val);

  if (it == val2txt_.end ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return std::string ("???");
  }

  U3_ASSERT (!it->second.empty ());
  return it->second;
}


auto
TextMinorExtCpu::get_val (const std::string& txt) const -> CpuMinorExts
{
  U3_ASSERT (!txt.empty ());
  auto it = txt2val_.find (txt);

  if (it == txt2val_.end ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return CpuMinorExts::empty;
  }
  return it->second;
}
}   // namespace libs::utility::sys::cpu
