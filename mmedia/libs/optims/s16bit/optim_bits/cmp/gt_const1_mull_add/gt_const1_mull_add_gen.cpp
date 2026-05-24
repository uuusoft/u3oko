/**
\file       gt_const1_mull_add_gen.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "gt_const1_mull_add.hpp"

namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add
{

inline void
check (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  info.dsts_[0].check ("dst 0 libs::optim::s16bit::bits::cmp::gt_const1_mull_add");

  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");

  info.srcs_[0].check ("src 0 libs::optim::s16bit::bits::cmp::gt_const1_mull_add");

  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
  U3_CHECK (1 == info.params_.consts_.size (), "consts not equal 1");
}
}   // namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add


#define SET_UNALIGNED_FUNCT
#include "gt_const1_mull_add_alu.cxx"
#include "gt_const1_mull_add_sse2.cxx"
#include "gt_const1_mull_add_avx1.cxx"
#include "gt_const1_mull_add_avx2.cxx"


#undef SET_UNALIGNED_FUNCT
#include "gt_const1_mull_add_alu.cxx"
#include "gt_const1_mull_add_sse2.cxx"
#include "gt_const1_mull_add_avx1.cxx"
#include "gt_const1_mull_add_avx2.cxx"
