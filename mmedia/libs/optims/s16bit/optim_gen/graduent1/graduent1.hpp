#pragma once
/**
\file       graduent1.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_gen

Формат источника 16 битовое слово, но перед вычислением формат усекается до беззнакового байта.
Полезна для эквивализации гистограммы, коррекции насыщенности и яркости и пр.
*/

namespace libs::optim::s16bit::gen::graduent1
{
inline void
check (::libs::optim::io::MCallInfo& cinfo)
{
  U3_CHECK (1 == cinfo.dsts_.size (), "dst not equal 1");

  cinfo.dsts_[0].check ("dst 0 gradient1");

  U3_CHECK (1 == cinfo.params_.consts_.size (), "consts not equal 1");
  U3_CHECK (1 == cinfo.params_.ints_.size (), "ints not equal 1");
  U3_CHECK (cinfo.params_.consts_[0], "0 const");
  U3_CHECK (cinfo.params_.ints_[0] > 0, "int less 1");
}

void alu (::libs::optim::io::MCallInfo& cinfo);
void sse2 (::libs::optim::io::MCallInfo& cinfo);
void avx1 (::libs::optim::io::MCallInfo& cinfo);
void avx2 (::libs::optim::io::MCallInfo& cinfo);
void neon (::libs::optim::io::MCallInfo& cinfo);
}   // namespace libs::optim::s16bit::gen::graduent1
