/**
\file       const_add_sub_mul_neg_abs_gen.cpp
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
check_consts (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  info.dsts_[0].check ("dst 0 check_consts");

  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
  U3_CHECK (1 == info.params_.consts_.size (), "count consts not equal 1");
}


inline void
check_sat (const ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dest not equal 1");
  info.dsts_[0].check ("dst 0 check_sat");
  U3_CHECK (info.params_.dest_mask_, "empty dest_mask");
}
}   // namespace libs::optim::s16bit::ops


#define SET_UNALIGNED_FUNCT
#undef SET_UNMASKDEST_FUNCT
#include "const_add_sub_mul_neg_abs.cxx"


// unaligned unmasking version
#define SET_UNALIGNED_FUNCT
#define SET_UNMASKDEST_FUNCT
#include "const_add_sub_mul_neg_abs.cxx"


// aligned masking version
#undef SET_UNALIGNED_FUNCT
#undef SET_UNMASKDEST_FUNCT
#include "const_add_sub_mul_neg_abs.cxx"


// aligned unmasking vesrion version
#undef SET_UNALIGNED_FUNCT
#define SET_UNMASKDEST_FUNCT
#include "const_add_sub_mul_neg_abs.cxx"
