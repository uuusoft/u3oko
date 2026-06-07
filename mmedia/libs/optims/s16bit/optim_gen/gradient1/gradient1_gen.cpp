/**
\file       graduent1_gen.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"

// old shit
namespace libs::optim::s16bit::gen::gradient1
{
#ifdef U3_FAKE_DISABLE
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

  if (1 != info.params_.consts_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (!info.params_.consts_[0])
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }
  return true;
}
#endif
}   // namespace libs::optim::s16bit::gen::gradient1


#ifdef U3_FAKE_DISABLE
#  define SET_UNALIGNED_FUNCT
#  include "gradient1_alu.cxx"
#  include "gradient1_sse2.cxx"
#  include "gradient1_avx1.cxx"
#  include "gradient1_avx2.cxx"


#  undef SET_UNALIGNED_FUNCT
#  include "gradient1_alu.cxx"
#  include "gradient1_sse2.cxx"
#  include "gradient1_avx1.cxx"
#  include "gradient1_avx2.cxx"
#endif
