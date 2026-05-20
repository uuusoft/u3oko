#pragma once
/**
\file			dct_func_mmx_sse_sse2.h
\date			23.03.2016
\author		Erashov Anton erashov2026@proton.me
\brief		Function IDCT coding
*/
#include "../../codec-funcs-const-vals.hpp"

namespace dlls::codecs::dct
{
typedef void (*unif_dct_func_type) (std::int16_t* coder_block);

void FDCTransform8x8MMX (std::int16_t* codec_block);
void IDCTransform8x8MMX (std::int16_t* codec_block);

void FDCTransform8x8SSE (std::int16_t* codec_block);
void IDCTransform8x8SSE (std::int16_t* codec_block);

void FDCTransform8x8SSE2 (std::int16_t* codec_block);
void IDCTransform8x8SSE2 (std::int16_t* codec_block);
}   // namespace dlls::codecs::dct
