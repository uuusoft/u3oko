/**
\file       ???.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../codec-funcs-includes_int.hpp"
#include "dct_func_mmx_sse_sse2.h"

#ifdef U3_CPU_X86

namespace dlls::codecs::dct
{
void
FDCTransform8x8SSE (std::int16_t* codec_block)
{
  ::libs::utility::checks::throw_exception ("failed");
  return FDCTransform8x8MMX (codec_block);
}


void
IDCTransform8x8SSE (std::int16_t* codec_block)
{
  ::libs::utility::checks::throw_exception ("failed");
  return IDCTransform8x8MMX (codec_block);
}
}   // namespace dlls::codecs::dct

#endif
