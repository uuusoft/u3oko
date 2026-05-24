/**
\file       base_3x3_avx2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_3x3.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::base::c3x3::consts
{
constexpr std::int32_t pxs_per_cycle = 5;   //<
}

namespace libs::optim::s16bit::conv::base::c3x3
{
#  define LOAD_STR(data, permute16, permute8)                                                          \
    data = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (csstr)); /*0123 456x xxxx xxxx*/ \
    data = _mm256_permutevar8x32_epi32 (data, permute16);                      /*0123 2323 2345 456x*/ \
    data = _mm256_shuffle_epi8 (data, permute8);                               /*0121 2323 4345 456x*/ \
    U3_FAST_MOVE_CPTR (csstr, stride);


#  define PROCESS_STR(str_mask)                   \
    himul = _mm256_mulhi_epi16 (data, str_mask);  \
    lomul = _mm256_mullo_epi16 (data, str_mask);  \
    mul1  = _mm256_unpacklo_epi16 (lomul, himul); \
    mul2  = _mm256_unpackhi_epi16 (lomul, himul); \
    akk1  = _mm256_add_epi32 (mul1, akk1);        \
    akk2  = _mm256_add_epi32 (mul2, akk2);


struct TAvx2CalcObj {
  U3_SET_TARGET_CPU (avx2)
  TAvx2CalcObj ()
  {
    str1_core_ = _mm256_setzero_si256 ();
    str2_core_ = _mm256_setzero_si256 ();
    str3_core_ = _mm256_setzero_si256 ();
    permute16_ = _mm256_setzero_si256 ();
    permute8_  = _mm256_setzero_si256 ();
  }


  U3_SET_TARGET_CPU (avx2)
  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    permute16_ = _mm256_set_epi32 (3, 2, 2, 1, 1, 1, 1, 0);
    permute8_  = _mm256_set_epi8 (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 5, 4, 15, 14, 13, 12, 11, 10, 9, 4, 3, 2, 5, 4, 3, 2, 1, 0);
    str1_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 0)));
    str2_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 1)));
    str3_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 2)));

    clone_core_str (str1_core_);
    clone_core_str (str2_core_);
    clone_core_str (str3_core_);
  }


  U3_SET_TARGET_CPU (avx2)
  void
  clone_core_str (__m256i& str)
  {
    const __m256i permute = _mm256_set_epi8 (
      0, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0);

    str = _mm256_permute4x64_epi64 (str, BOOST_BINARY (00000000));   // 0, 1, 2, x, 0, 1, 2, x,   0, 1, 2, x,   0, 1, 2, x
    str = _mm256_shuffle_epi8 (str, permute);                        // 0, 1, 2, 0, 1, 2, 0, 1,   2, 0, 1, 2,   0, 1, 2, x
  }


  U3_SET_TARGET_CPU (avx2)
  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    __m256i data;
    __m256i himul;
    __m256i lomul;
    __m256i mul1;
    __m256i mul2;
    __m256i akk1 = _mm256_setzero_si256 ();
    __m256i akk2 = akk1;

    // #  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    // #  else
    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str1_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str2_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str3_core_);
    // #  endif

    __m256i       fakk      = _mm256_setzero_si256 ();
    const __m256i fpermute1 = _mm256_setr_epi32 (0, 3, 4, 5, 7, 7, 7, 7);
    const __m256i fmask     = _mm256_setr_epi32 (-1, -1, -1, -1, -1, -1, -1, 0);
    __m256i       ftemp;

    ftemp = akk1;                                             // A1A2A3B1  C1D1D2D3
    ftemp = _mm256_and_si256 (ftemp, fmask);                  // A1A2A3B1  C1D1D200
    ftemp = _mm256_permutevar8x32_epi32 (ftemp, fpermute1);   // A1B1C1D1  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    const __m256i fpermute2 = _mm256_setr_epi32 (0, 7, 7, 5, 7, 7, 7, 7);

    akk1  = _mm256_srli_si256 (akk1, 4);                     // A2A3B100  D1D2D300
    ftemp = _mm256_permutevar8x32_epi32 (akk1, fpermute2);   // A20000D2  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    const __m256i fpermute3 = _mm256_setr_epi32 (1, 7, 7, 6, 7, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk1, fpermute3);   // A30000D3  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    const __m256i fpermute4 = _mm256_setr_epi32 (7, 0, 2, 7, 4, 7, 7, 7);

    akk2  = _mm256_and_si256 (akk2, fmask);                  // B2B3C2C3  E1E2E300
    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute4);   // 00B2C200  E1000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    const __m256i fpermute5 = _mm256_setr_epi32 (7, 1, 3, 7, 5, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute5);   // 00B3C300  E2000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    // const __m256i fpermute6  = _mm256_setr_epi32( 7, 7, 7, 7, 6, 7, 7, 7 );

    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute5);   // 00000000  E3000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    const __m256i mulkoeff = _mm256_setr_epi32 (mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff);

    akk1 = fakk;

    akk1 = _mm256_mullo_epi32 (akk1, mulkoeff);
    akk1 = _mm256_srai_epi32 (akk1, U3_SHIFT_MUL_KOEFF_CONVOLUTION);
    akk2 = _mm256_permute2x128_si256 (akk1, akk1, 1);
    akk1 = _mm256_packus_epi32 (akk1, akk2);

    _mm256_storeu_si256 (U3_CAST_REINTERPRET< __m256i* > (dstr), akk1);
  }


  __m256i str1_core_;   //<
  __m256i str2_core_;   //<
  __m256i str3_core_;   //<
  __m256i permute16_;   //<
  __m256i permute8_;    //<
};


struct TModAvx2CalcObj : public TAvx2CalcObj {
  TModAvx2CalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    TAvx2CalcObj::init (info, pmask);
  }


  U3_SET_TARGET_CPU (avx2)
  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    __m256i data;
    __m256i himul;
    __m256i lomul;
    __m256i mul1;
    __m256i mul2;
    __m256i akk1 = _mm256_setzero_si256 ();
    __m256i akk2 = akk1;

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str1_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str2_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str3_core_);

    __m256i fakk         = _mm256_setzero_si256 ();
    __m256i fpermute_all = _mm256_setr_epi32 (0, 3, 4, 5, 7, 7, 7, 7);
    __m256i fmask_mull   = _mm256_setr_epi32 (-1, -1, -1, -1, -1, -1, -1, 0);
    __m256i ftemp;

    ftemp = akk1;                                                // A1A2A3B1  C1D1D2D3
    ftemp = _mm256_and_si256 (ftemp, fmask_mull);                // A1A2A3B1  C1D1D200
    ftemp = _mm256_permutevar8x32_epi32 (ftemp, fpermute_all);   // A1B1C1D1  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    akk2 = _mm256_and_si256 (akk2, fmask_mull);   // B2B3C2C3  E1E2E300

    fpermute_all = _mm256_setr_epi32 (0, 7, 7, 5, 7, 7, 7, 7);

    akk1  = _mm256_srli_si256 (akk1, 4);                        // A2A3B100  D1D2D300
    ftemp = _mm256_permutevar8x32_epi32 (akk1, fpermute_all);   // A20000D2  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    fpermute_all = _mm256_setr_epi32 (1, 7, 7, 6, 7, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk1, fpermute_all);   // A30000D3  00000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    fpermute_all = _mm256_setr_epi32 (7, 0, 2, 7, 4, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute_all);   // 00B2C200  E1000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    fpermute_all = _mm256_setr_epi32 (7, 1, 3, 7, 5, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute_all);   // 00B3C300  E2000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    fpermute_all = _mm256_setr_epi32 (7, 7, 7, 7, 6, 7, 7, 7);

    ftemp = _mm256_permutevar8x32_epi32 (akk2, fpermute_all);   // 00000000  E3000000
    fakk  = _mm256_add_epi32 (fakk, ftemp);

    fmask_mull = _mm256_setr_epi32 (mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff, mul_koeff);

    akk1 = _mm256_abs_epi32 (fakk);
    akk1 = _mm256_mullo_epi32 (akk1, fmask_mull);
    akk1 = _mm256_srai_epi32 (akk1, U3_SHIFT_MUL_KOEFF_CONVOLUTION);
    akk2 = _mm256_permute2x128_si256 (akk1, akk1, 1);
    akk1 = _mm256_packus_epi32 (akk1, akk2);

    _mm256_storeu_si256 (U3_CAST_REINTERPRET< __m256i* > (dstr), akk1);
  }
};


U3_SET_TARGET_CPU (avx2)
void
mod_avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TModAvx2CalcObj, cores::values_core_type, TEmptyPostProcessor, consts::size_core, consts::pxs_per_cycle, 3 > (info);
  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TAvx2CalcObj, cores::values_core_type, TEmptyPostProcessor, consts::size_core, consts::pxs_per_cycle, 3 > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::base::c3x3

#endif
