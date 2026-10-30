/*
\file       text-minor-ext-cpu.cpp
\date       02.06.2022
\author     Erashov Anton erashov2026@proton.me
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
    ::libs::utility::checks::mark ("failed");
    return std::string ("???");
  }

  ::libs::utility::checks::throw_ifn (!it->second.empty ());
  return it->second;
}


auto
TextMinorExtCpu::get_val (const std::string& txt) const -> CpuMinorExts
{
  ::libs::utility::checks::throw_ifn (!txt.empty ());
  auto it = txt2val_.find (txt);

  if (it == txt2val_.end ())
  {
    ::libs::utility::checks::throw_exception ("failed");
    return CpuMinorExts::empty;
  }
  return it->second;
}
}   // namespace libs::utility::sys::cpu
