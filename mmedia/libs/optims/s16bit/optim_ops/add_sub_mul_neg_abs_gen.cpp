/**
\file       add_sub_mul_neg_abs_gen.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_ops
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"

namespace libs::optim::s16bit::ops
{
inline void
check (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1 ");
  info.dsts_[0].check ("dst 0 libs::optim::s16bit::ops");

  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  info.srcs_[0].check ("src 0 libs::optim::s16bit::ops");

  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
}


inline void
check_rshifts (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  info.dsts_[0].check ("dst 0 libs::optim::s16bit::ops check_rshifts");

  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");

  info.srcs_[0].check ("src 0 libs::optim::s16bit::ops check_rshifts");

  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
  U3_CHECK (2 == info.params_.consts_.size (), "count  consts not equal 2");
  U3_CHECK (info.params_.consts_[0], "empty consts[0]");
  U3_CHECK (info.params_.consts_[1], "empty consts[1]");
  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
}
}   // namespace libs::optim::s16bit::ops


#define SET_UNALIGNED_FUNCT

#include "add_sub_mul_neg_abs.cxx"

#define ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord
#include "add_sub_mul_neg_abs.cxx"
#undef ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord

#define ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord
#include "add_sub_mul_neg_abs.cxx"
#undef ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord

#undef SET_UNALIGNED_FUNCT


#include "add_sub_mul_neg_abs.cxx"

#define ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord
#include "add_sub_mul_neg_abs.cxx"
#undef ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord

#define ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord
#include "add_sub_mul_neg_abs.cxx"
#undef ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord
