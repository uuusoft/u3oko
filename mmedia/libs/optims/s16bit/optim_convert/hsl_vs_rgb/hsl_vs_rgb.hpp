#pragma once
/**
\file       hsl_vs_rgb.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_convert
*/

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
void rgb24_to_hsl_alu (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_alu (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_sse1 (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_sse1 (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_sse2 (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_sse2 (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_sse3 (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_sse3 (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_avx1 (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_avx1 (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_avx2 (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_avx2 (::libs::optim::io::MCallInfo& info);

void rgb24_to_hsl_neon (::libs::optim::io::MCallInfo& info);
void hsl_to_rgb24_neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb
