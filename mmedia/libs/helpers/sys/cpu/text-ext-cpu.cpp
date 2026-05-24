/**
\file       text-ext-cpu.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../helpers-lib-includes_int.hpp"
#include "text-ext-cpu.hpp"

namespace libs::helpers::sys::cpu
{
TextExtCpu::TextExtCpu ()
{
  // clang-format off
  static const std::string txts[] = {
    "default", "max", "min", "alu", "mmx", "sse2", "sse3", "sse4.1", "sse4.2", "avx1", "avx2", "neon"
  };

  static const CpuExts exts[] = {
    CpuExts::usual, 
    CpuExts::max, 
    CpuExts::min, 
    CpuExts::alu, 
    CpuExts::mmx, 
    CpuExts::sse2, 
    CpuExts::sse3, 
    CpuExts::sse4_1, 
    CpuExts::sse4_2, 
    CpuExts::avx1, 
    CpuExts::avx2, 
    CpuExts::neon
  };
  // clang-format on

  for (std::size_t indx = 0; indx < std::size (txts); ++indx)
  {
    txt2val_.insert (std::pair< std::string, CpuExts > (txts[indx], exts[indx]));
    val2txt_.insert (std::pair< CpuExts, std::string > (exts[indx], txts[indx]));
  }
}


std::string
TextExtCpu::get_text (const CpuExts& val) const
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


CpuExts
TextExtCpu::get_val (const std::string& txt) const
{
  U3_ASSERT (!txt.empty ());
  auto it = txt2val_.find (txt);
  if (it == txt2val_.end ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return CpuExts::usual;
  }
  return it->second;
}
}   // namespace libs::helpers::sys::cpu
