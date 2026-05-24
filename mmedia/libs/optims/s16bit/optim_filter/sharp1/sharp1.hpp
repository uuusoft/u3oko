#pragma once
/**
\file       sharp1.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
P5 = ( (P5 - P1 ) + (P5 - P2 ) + (P5 - P3) + (P5 - P4 ) + (P5 - P6) + (P5 - P7) + (P5 - P8) + (P5 - P9 ) ) / 8
P5 = (2 * P5 ) / 16 - (2 * (P1+P2+P3+P4+P6+P7+P8+P9 ) ) / 16
P5 = ( 3 * P5 ) / 16 - ( 3 * (P2+P3+P6+P8+P9 ) ) / 16

P1 P2 P3
P4 P5 P6
P7 P8 P9
P5 = ( (P5-P1 )+(P5-P2 )+(P5-P3)+(P5-P4 )+(P5-P6)+(P5-P7)+(P5-P8)+(P5-P9 ) ) / 8
P5 = (8*P5-(P1+P2+P3+P4+P6+P7+P8+P9 ) ) / 8
P5 = P5-(P1+P2+P3+P4+P6+P7+P8+P9 ) / 8

P5 = ( (P5-P2 )+(P5-P3)+(P5-P6)+(P5-P8)+(P5-P9 ) ) / 5
P5 = (5*P5-(P2+P3+P6+P8+P9 ) ) / 5
P5 = P5-(P2+P3+P6+P8+P9 ) / 5
*/

// old shit
// #include "../..???/includes.hpp"
namespace libs::optim::s16bit::filter::sharp1
{
#if 0
void alu (::libs::optim::io::MCallInfo& info);
void mmx (::libs::optim::io::MCallInfo& info);
void sse1 (::libs::optim::io::MCallInfo& info);
void udest_sse1 (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void udest_sse2 (::libs::optim::io::MCallInfo& info);
#endif
}   // namespace libs::optim::s16bit::filter::sharp1
