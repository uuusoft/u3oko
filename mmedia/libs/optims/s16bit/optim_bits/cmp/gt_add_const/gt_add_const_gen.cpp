/**
\file       gt_add_const_gen_cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "gt_add_const.hpp"

namespace libs::optim::s16bit::bits::cmp::gt_add_const
{

inline void
check (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");
  info.dsts_[0].check ("dst 0 bits::cmp::gt_add_const");
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  info.srcs_[0].check ("src 0 bits::cmp::gt_add_const");
  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
  U3_CHECK (1 == info.params_.consts_.size (), "const not equal 1");
}
}   // namespace libs::optim::s16bit::bits::cmp::gt_add_const


#define SET_UNALIGNED_FUNCT
#include "gt_add_const_alu.cxx"
#include "gt_add_const_sse2.cxx"
#include "gt_add_const_avx1.cxx"
#include "gt_add_const_avx2.cxx"


#undef SET_UNALIGNED_FUNCT
#include "gt_add_const_alu.cxx"
#include "gt_add_const_sse2.cxx"
#include "gt_add_const_avx1.cxx"
#include "gt_add_const_avx2.cxx"
