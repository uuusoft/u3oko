/**
\file       *.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_9x9.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::base::c9x9::consts
{
constexpr int pxs_per_cycle = 1;   //<
}

namespace libs::optim::s16bit::conv::base::c9x9
{
#  define PROCESS_STR(Str)                                                                         \
    str_mask = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(*mask).get (0, Str))); \
    data     = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (csstr));                 \
    U3_FAST_MOVE_CPTR (csstr, stride);                                                             \
    himul    = _mm256_mulhi_epi16 (data, str_mask);                                                \
    lomul    = _mm256_mullo_epi16 (data, str_mask);                                                \
    str_mul1 = _mm256_unpacklo_epi16 (lomul, himul);                                               \
    str_mul2 = _mm256_unpackhi_epi16 (lomul, himul);                                               \
    str_mul  = _mm256_add_epi32 (str_mul1, str_mul2);                                              \
    akk      = _mm256_add_epi32 (str_mul, akk);


struct TAvx2CalcObj {
  TAvx2CalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::TCore** pmask)
  {
  }

  U3_SET_TARGET_CPU (avx2)
  void
  get_res (
    const std::int16_t  mul_koeff,
    const std::int16_t* csstr,
    const cores::TCore* mask,
    const std::uint32_t stride,
    std::int32_t*       tress,
    std::int16_t*       dstr)
  {
    std::int32_t& tres = *tress;
    __m256i       str_mask;
    __m256i       data;
    __m256i       himul;
    __m256i       lomul;
    __m256i       str_mul;
    __m256i       str_mul1;
    __m256i       str_mul2;
    __m256i       akk = _mm256_setzero_si256 ();

    PROCESS_STR (0);
    PROCESS_STR (1);
    PROCESS_STR (2);
    PROCESS_STR (3);
    PROCESS_STR (4);
    PROCESS_STR (5);
    PROCESS_STR (6);
    PROCESS_STR (7);
    PROCESS_STR (8);

    akk = _mm256_hadd_epi32 (akk, akk);   // 8->4
    akk = _mm256_hadd_epi32 (akk, akk);   // 4->2

#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    tres = _mm256_extract_epi32 (akk, 0);
    tres += _mm256_extract_epi32 (akk, 4);
#  else
    tres = akk.m256i_i32[0];
    tres += akk.m256i_i32[4];
#  endif
  }
};


struct TModAvx2CalcObj : public TAvx2CalcObj {
  TModAvx2CalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::TCore** pmask)
  {
    TAvx2CalcObj::init (info, pmask);
  }

  void
  get_res (
    const std::int16_t  mul_koeff,
    const std::int16_t* csstr,
    const cores::TCore* mask,
    const std::uint32_t stride,
    std::int32_t*       tress,
    std::int16_t*       dstr)
  {
    TAvx2CalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);
    tress[0] = std::abs (tress[0]);
  }
};


U3_SET_TARGET_CPU (avx2)
void
mod_avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TModAvx2CalcObj, cores::TCore, TPostProcessor, consts::size_core > (info);
  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TAvx2CalcObj, cores::TCore, TPostProcessor, consts::size_core > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::base::c9x9

#endif
