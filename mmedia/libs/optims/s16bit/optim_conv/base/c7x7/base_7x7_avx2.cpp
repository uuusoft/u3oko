/**
\file       base_7x7_avx2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_7x7.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::conv::base::c7x7::consts
{
constexpr std::int32_t pxs_per_cycle = 2;   //<
}

namespace libs::optim::s16bit::conv::base::c7x7
{
#  define LOAD_RAW_STR(Data) Data = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (csstr));

#  define LOAD_STR(Data, Permute16, Permute8)                                      \
    LOAD_RAW_STR (Data);                                   /*0123 4567 xxxx xxxx*/ \
    Data  = _mm256_permutevar8x32_epi32 (Data, Permute16); /*0123 4567 2345 67xx*/ \
    Data  = _mm256_shuffle_epi8 (Data, Permute8);          /*0123 4561 2345 67xx*/ \
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);


#  define PROCESS_STR(Data, Mask)                 \
    himul = _mm256_mulhi_epi16 (Data, Mask);      \
    lomul = _mm256_mullo_epi16 (Data, Mask);      \
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
    str4_core_ = _mm256_setzero_si256 ();
    str5_core_ = _mm256_setzero_si256 ();
    str6_core_ = _mm256_setzero_si256 ();
    str7_core_ = _mm256_setzero_si256 ();
    permute16_ = _mm256_setzero_si256 ();
    permute8_  = _mm256_setzero_si256 ();
    mask_akk1_ = _mm256_setzero_si256 ();
    mask_akk2_ = _mm256_setzero_si256 ();
  }


  U3_SET_TARGET_CPU (avx2)
  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    permute16_ = _mm256_set_epi32 (0, 3, 2, 1, 3, 2, 1, 0);
    permute8_  = _mm256_set_epi8 (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 3, 2, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

    mask_akk1_ = _mm256_setzero_si256 ();
    mask_akk2_ = _mm256_set1_epi32 (-1);

#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    U3_ASSERT_SIGNAL ("failed");
    // mask_akk2_ = _mm256_insert_epi32( mask_akk2_, 0, 3 );
    // mask_akk2_ = _mm256_insert_epi32( mask_akk2_, 0, 6 );
    // mask_akk2_ = _mm256_insert_epi32( mask_akk2_, 0, 7 );
#  else
    mask_akk2_.m256i_u32[3] = 0;
    mask_akk2_.m256i_u32[6] = 0;
    mask_akk2_.m256i_u32[7] = 0;
#  endif

    str1_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 0)));
    str2_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 1)));
    str3_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 2)));
    str4_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 3)));
    str5_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 4)));
    str6_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 5)));
    str7_core_ = _mm256_lddqu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (&(**pmask).get (0, 6)));

    clone_core_str (str1_core_);
    clone_core_str (str2_core_);
    clone_core_str (str3_core_);
    clone_core_str (str4_core_);
    clone_core_str (str5_core_);
    clone_core_str (str6_core_);
    clone_core_str (str7_core_);
  }


  U3_SET_TARGET_CPU (avx2)
  void
  clone_core_str (__m256i& str)
  {
    // 1 px
    //-
    // 2 px
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 0), 7);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 1), 8);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 2), 9);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 3), 10);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 4), 11);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 5), 12);
    str = _mm256_insert_epi16 (str, _mm256_extract_epi16 (str, 6), 13);
#  else
    str.m256i_i16[7]  = str.m256i_i16[0];
    str.m256i_i16[8]  = str.m256i_i16[1];
    str.m256i_i16[9]  = str.m256i_i16[2];
    str.m256i_i16[10] = str.m256i_i16[3];
    str.m256i_i16[11] = str.m256i_i16[4];
    str.m256i_i16[12] = str.m256i_i16[5];
    str.m256i_i16[13] = str.m256i_i16[6];
#  endif
    return;
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
    __m256i akk1 = _mm256_setzero_si256 ();
    __m256i akk2 = _mm256_setzero_si256 ();
    __m256i akk3 = _mm256_setzero_si256 ();
    __m256i data;
    __m256i himul;
    __m256i lomul;
    __m256i mul1;
    __m256i mul2;

    // #  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    // #  else
    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str1_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str2_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str3_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str4_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str5_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str6_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (data, str7_core_);
    // #  endif

    /*
      akk1 = px0 px0 px0 px0 px1 px1 px1 px1
      akk2 = px0 px0 px0 px1 px1 px1 pxx pxx
      */
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    tress[1] = _mm256_extract_epi32 (akk2, 3);
#  else
    tress[1] = akk2.m256i_i32[3];
#  endif

    akk2 = _mm256_and_si256 (akk2, mask_akk2_);   // akk2 = px0 px0 px0 0 px1 px1 0 0
    akk2 = _mm256_add_epi32 (akk1, akk2);         // akk2 = px0 + px0,  px0 + px0, px0 + px0, px0 + 0, px1 + px1, px1 + px1, px1 + 0, px1 + 0
    akk2 = _mm256_hadd_epi32 (akk2, akk2);
    akk3 = _mm256_hadd_epi32 (akk2, akk2);

#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    tress[0] = _mm256_extract_epi32 (akk3, 0);
    tress[1] += _mm256_extract_epi32 (akk3, 4);
#  else
    tress[0] = akk3.m256i_i32[0];
    tress[1] += akk3.m256i_i32[4];
#  endif
  }

  __m256i str1_core_;
  __m256i str2_core_;
  __m256i str3_core_;
  __m256i str4_core_;
  __m256i str5_core_;
  __m256i str6_core_;
  __m256i str7_core_;

  __m256i permute16_;
  __m256i permute8_;

  __m256i mask_akk1_;
  __m256i mask_akk2_;
};


struct TModAvx2CalcObj : public TAvx2CalcObj {
  TModAvx2CalcObj () = default;

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    TAvx2CalcObj::init (info, pmask);
  }

  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    int*                           tress,
    std::int16_t*                  dstr)
  {
    TAvx2CalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);
    tress[0] = std::abs (tress[0]);
    tress[1] = std::abs (tress[1]);
  }
};


U3_SET_TARGET_CPU (avx2)
void
mod_avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TModAvx2CalcObj, cores::values_core_type, TPostProcessor, consts::size_core, consts::pxs_per_cycle > (info);
  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TAvx2CalcObj, cores::values_core_type, TPostProcessor, consts::size_core, consts::pxs_per_cycle > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::base::c7x7

#endif
