/**
\file       key_source_gen.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits

Dp = Sp != 0 ? Sp : Dp;
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "key_source.hpp"

namespace libs::optim::s16bit::bits::key_source
{
inline void
check (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");
  info.dsts_[0].check ("dst 0 libs::optim::s16bit::bits::key_source");

  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  info.srcs_[0].check ("src 0 libs::optim::s16bit::bits::key_source");

  U3_CHECK (info.params_.dest_mask_, "empty mask_dest");
}
}   // namespace libs::optim::s16bit::bits::key_source


#define SET_UNALIGNED_FUNCT
#include "key_source_alu.cxx"
#include "key_source_sse2.cxx"
#include "key_source_avx1.cxx"
#include "key_source_avx2.cxx"


#undef SET_UNALIGNED_FUNCT
#include "key_source_alu.cxx"
#include "key_source_sse2.cxx"
#include "key_source_avx1.cxx"
#include "key_source_avx2.cxx"
