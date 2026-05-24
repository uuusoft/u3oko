#pragma once
/**
\file       ???.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../codec-funcs-const-vals.hpp"

namespace codecs
{
void idct_mm32 (int16_t *block);
}
