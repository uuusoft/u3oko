#pragma once
/**
\file       base_11x11.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_optim_conv
*/
#include "consts11x11.hpp"
#include "cores11x11.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/optim-conv-move_alg.hpp"

namespace libs::optim::s16bit::conv::base::c11x11
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);

void mod_alu (::libs::optim::io::MCallInfo& info);
void mod_sse2 (::libs::optim::io::MCallInfo& info);
void mod_avx1 (::libs::optim::io::MCallInfo& info);
void mod_avx2 (::libs::optim::io::MCallInfo& info);
void mod_neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::conv::base::c11x11
