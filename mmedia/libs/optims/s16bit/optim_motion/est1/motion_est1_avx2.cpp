/**
\file     motion_est1_sse1.cpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     28.08.2016
\project  u3_optim_libs_motion
\brief    Оценка движения в кадре
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"
#include "move_alg.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::motion::est1
{

struct TAvx2CalcObj final {
  U3_SET_TARGET_CPU (avx2)
  TAvx2CalcObj () :
    init_ (false), max_mask_ (0)
  {
    masks_[0] = _mm256_setzero_si256 ();
    masks_[1] = masks_[0];
  }


  void
  init (::libs::optim::io::MCallInfo& info)
  {
  }


  U3_SET_TARGET_CPU (avx2)
  int
  get_res (
    const std::int16_t* src1,
    const std::int16_t* src2,
    const std::int16_t  size_block,
    const std::size_t   stride)
  {
    std::int32_t ret = 0;

    U3_ASSERT (size_block <= 32);
    U3_ASSERT (size_block <= 16);

    update_mask (size_block);

    __m256i iymm0     = _mm256_setzero_si256 ();
    __m256i iymm1     = _mm256_setzero_si256 ();
    __m256i iymm2     = _mm256_setzero_si256 ();
    __m256i iymm4     = masks_[1];
    __m128i iymm0_128 = _mm_setzero_si128 ();
    __m128i iymm2_128 = _mm_setzero_si128 ();

    for (std::uint32_t indxy = 0; indxy < U3_CAST_UINT32 (size_block); ++indxy)
    {
      const __m256i* isrc1 = U3_CAST_REINTERPRET< const __m256i* > (src1);
      const __m256i* isrc2 = U3_CAST_REINTERPRET< const __m256i* > (src2);

      // базовое сравнение по горизонтали, которое есть всегда
      {
        iymm0 = _mm256_lddqu_si256 (isrc1);
        // iymm0 = _mm256_and_si256( iymm0, iymm3);

        iymm1 = _mm256_lddqu_si256 (isrc2);
        // iymm1 = _mm256_and_si256( iymm1, iymm3);

        iymm0 = _mm256_subs_epi16 (iymm0, iymm1);
        iymm0 = _mm256_abs_epi16 (iymm0);
        iymm2 = _mm256_add_epi16 (iymm2, iymm0);
      }

      // дополнительное сравнение по горизонтали, если размер блока больше 16.
      if (2 == max_mask_)
      {
        iymm0 = _mm256_lddqu_si256 (isrc1 + 1);
        iymm0 = _mm256_and_si256 (iymm0, iymm4);

        iymm1 = _mm256_lddqu_si256 (isrc2 + 1);
        iymm1 = _mm256_and_si256 (iymm1, iymm4);

        iymm0 = _mm256_subs_epi16 (iymm0, iymm1);
        iymm0 = _mm256_abs_epi16 (iymm0);
        iymm2 = _mm256_add_epi16 (iymm2, iymm0);
      }

      U3_FAST_MOVE_CPTR (src1, stride);
      U3_FAST_MOVE_CPTR (src2, stride);
    }

    iymm1     = _mm256_permute2f128_si256 (iymm2, iymm2, 1);
    iymm0_128 = _mm256_castsi256_si128 (iymm1);
    iymm2_128 = _mm256_castsi256_si128 (iymm2);
    iymm0     = _mm256_cvtepi16_epi32 (iymm0_128);
    iymm1     = _mm256_cvtepi16_epi32 (iymm2_128);

    iymm0 = _mm256_hadd_epi32 (iymm0, iymm1);   // 4
    iymm0 = _mm256_hadd_epi32 (iymm0, iymm0);   // 2
    iymm0 = _mm256_hadd_epi32 (iymm0, iymm0);   // 1


#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    ret += _mm256_extract_epi32 (iymm0, 0);
    ret += _mm256_extract_epi32 (iymm0, 4);
#  else
    ret += iymm0.m256i_i32[0];
    ret += iymm0.m256i_i32[4];
#  endif
    return ret;
  }


  protected:
  U3_SET_TARGET_CPU (avx2)
  void
  update_mask (const std::int16_t size_block)
  {
    if (init_)
    {
      return;
    }

    init_     = true;
    max_mask_ = 0;

    std::int16_t calc_size_block = size_block;

    for (std::uint32_t fill_mask = 0; calc_size_block > 0 && fill_mask < std::size (masks_); ++fill_mask)
    {
      masks_[fill_mask] = _mm256_setzero_si256 ();

      for (short findx = 0; findx < calc_size_block; ++findx)
      {
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
        // masks_[ fill_mask ] = _mm256_insert_epi16( masks_[ fill_mask ], 0xFFFF, findx );
#  else
        masks_[fill_mask].m256i_u16[findx] = 0xFFFF;
#  endif
      }

      calc_size_block -= 16;
      ++max_mask_;
    }
  }


  private:
  bool          init_;       //<  DEFINE
  __m256i       masks_[2];   //<  Размер блока не может быть больше 32 std::int16_t, это 64 byte, или 512 bit, или 2 _m256
  std::uint32_t max_mask_;   //<  DEFINE
};


U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TAvx2CalcObj > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::motion::est1

#endif
