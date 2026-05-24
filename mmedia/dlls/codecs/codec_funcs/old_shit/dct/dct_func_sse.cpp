/**
\file       ???.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../codec-funcs-includes_int.hpp"
#include "dct_func_mmx_sse_sse2.h"

#if defined(U3_CPU_X86)

namespace dlls::codecs::dct
{
void
FDCTransform8x8SSE (std::int16_t* codec_block)
{
  U3_ASSERT_SIGNAL ("failed");
  return FDCTransform8x8MMX (codec_block);
}


void
IDCTransform8x8SSE (std::int16_t* codec_block)
{
  U3_ASSERT_SIGNAL ("failed");
  return IDCTransform8x8MMX (codec_block);
}
}   // namespace dlls::codecs::dct

#endif
