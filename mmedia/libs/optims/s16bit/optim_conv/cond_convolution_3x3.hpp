#pragma once
/**
\file       cond_convolution_3x3.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "optim-conv-const-vals.hpp"

// old shit ???
namespace libs::optim::s16bit::conv::cond
{
// в зависимоости от значения в буфере-условий для пикселя применяется рзаличные маски
// полезно, например, для алиясинга линий
//  OUT[x,y] = IN[x,y] * ( CONDT[x,y] < bound ? mask1 : mask2 )

void cond_b3x3_alu (::libs::optim::io::MCallInfo& info);
void cond_b3x3_sse2 (::libs::optim::io::MCallInfo& info);
void cond_b3x3_avx1 (::libs::optim::io::MCallInfo& info);
void cond_b3x3_avx2 (::libs::optim::io::MCallInfo& info);

void mod_cond_b3x3_alu (::libs::optim::io::MCallInfo& info);
void mod_cond_b3x3_sse2 (::libs::optim::io::MCallInfo& info);
void mod_cond_b3x3_avx1 (::libs::optim::io::MCallInfo& info);
void mod_cond_b3x3_avx2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::conv::cond
