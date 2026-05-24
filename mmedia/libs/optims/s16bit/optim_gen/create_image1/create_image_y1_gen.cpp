/**
\file       create_image_y1_gen.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_freq
GenerateImageFromYConstSignedWordXXXFunct
Dp[ x, y ] = ( Const2 - abs( Const1 - y ) * abs( Const1 - y ) )
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"

// old shit
namespace libs::optim::s16bit::gen::create_image1
{
#if 0
inline bool
check (const ::libs::optim::io::MCallInfo& info)
{
  if (1 != info.dsts_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  if (!info.dsts_[0].check ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  if (2 != info.params_.consts_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  if (!info.params_.consts_[0])
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  if (!info.params_.consts_[1])
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  return true;
}
#endif
}   // namespace libs::optim::s16bit::gen::create_image1


#if 0
#  undef SET_UNALIGNED_FUNCT
#  undef SET_UNMASKDEST_FUNCT
//aligned masking version
#  include "create_image_y1_alu.cxx"
#  include "create_image_y1_sse2.cxx"
#  include "create_image_y1_avx1.cxx"
#  include "create_image_y1_avx2.cxx"

#  define SET_UNALIGNED_FUNCT
//unaligned masking version
#  include "create_image_y1_alu.cxx"
#  include "create_image_y1_sse2.cxx"
#  include "create_image_y1_avx1.cxx"
#  include "create_image_y1_avx2.cxx"

#endif
