#pragma once
/**
\file       gradient1.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen

const1->const2
  ^       ^
  |       |
const3->const4

gradiant fill
*/

// old shit
namespace libs::optim::s16bit::gen::gradient1
{
#ifdef U3_FAKE_DISABLE
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void udest_sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
#endif
}   // namespace libs::optim::s16bit::gen::gradient1
