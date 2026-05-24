#pragma once
/**
\file		\fdct.h
\date		.03.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\brief		Function FDCT coding
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../codec-funcs-const-vals.hpp"

namespace dlls::codecs::dct
{
void fdct_mm32 (short *blk);
void idct_mm32 (short *blk);
bool jpeg_fdct_float (float *data);
}   // namespace dlls::codecs::dct
