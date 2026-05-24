/**
\file       *.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_5x5.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::base::c5x5::consts
{
constexpr std::int32_t pxs_per_cycle = 3;   //<
}

namespace libs::optim::s16bit::conv::base::c5x5
{
#  define LOAD_RAW_STR(data) data = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (csstr));


#  define LOAD_STR(data, permute16, permute8)                                     \
    LOAD_RAW_STR (data);                                  /*0123 456x xxxx xxxx*/ \
    data = _mm256_permutevar8x32_epi32 (data, permute16); /*0123 4523 4523 456x*/ \
    data = _mm256_shuffle_epi8 (data, permute8);          /*0123 4123 4523 456x*/ \
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
    str4_core_ = _mm256_setzero_si256 ();
    str5_core_ = _mm256_setzero_si256 ();
    permute16_ = _mm256_setzero_si256 ();
    permute8_  = _mm256_setzero_si256 ();
  }


  U3_SET_TARGET_CPU (avx2)
  void
  init (::libs::optim::io::MCallInfo& info, const cores::TCore** pmask)
  {
    permute16_ = _mm256_set_epi32 (3, 2, 1, 2, 1, 2, 1, 0);
    permute8_  = _mm256_set_epi8 (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

    str1_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 0)));
    str2_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 1)));
    str3_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 2)));
    str4_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 3)));
    str5_core_ = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (&(**pmask).get (0, 4)));

    clone_core_str (str1_core_);
    clone_core_str (str2_core_);
    clone_core_str (str3_core_);
    clone_core_str (str4_core_);
    clone_core_str (str5_core_);
  }


  U3_SET_TARGET_CPU (avx2)
  void
  clone_core_str (__m256i& str)
  {
    U3_ALIGN_DEFAULT std::int16_t temp[16];
    _mm256_store_si256 (U3_CAST_REINTERPRET< __m256i* > (temp), str);

    // 1 px
    //-
    // 2 px
    temp[5] = temp[0];
    temp[6] = temp[1];
    temp[7] = temp[2];
    temp[8] = temp[3];
    temp[9] = temp[4];
    // 3 px
    temp[10] = temp[0];
    temp[11] = temp[1];
    temp[12] = temp[2];
    temp[13] = temp[3];
    temp[14] = temp[4];

    str = _mm256_load_si256 (U3_CAST_REINTERPRET< __m256i* > (temp));
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

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str4_core_);

    LOAD_STR (data, permute16_, permute8_);
    PROCESS_STR (str5_core_);

    /*
      akk1 = px0 px0 px0 px0 px1 px1 px2 px2
      akk2 = px0 px1 px1 px1 px2 px2 px2 pxx
      */
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
    // tress[0] = _mm256_extract_epi32 (akk1, 0);
#  else
    tress[0] = akk1.m256i_i32[0];
    tress[0] += akk1.m256i_i32[1];
    tress[0] += akk1.m256i_i32[2];
    tress[0] += akk1.m256i_i32[3];
    tress[0] += akk2.m256i_i32[0];

    tress[1] = akk1.m256i_i32[4];
    tress[1] += akk1.m256i_i32[5];
    tress[1] += akk2.m256i_i32[1];
    tress[1] += akk2.m256i_i32[2];
    tress[1] += akk2.m256i_i32[3];

    tress[2] = akk1.m256i_i32[6];
    tress[2] += akk1.m256i_i32[7];
    tress[2] += akk2.m256i_i32[4];
    tress[2] += akk2.m256i_i32[5];
    tress[2] += akk2.m256i_i32[6];
#  endif
  }

  __m256i str1_core_;   //<
  __m256i str2_core_;   //<
  __m256i str3_core_;   //<
  __m256i str4_core_;   //<
  __m256i str5_core_;   //<
  __m256i permute16_;   //<
  __m256i permute8_;    //<
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
  }
};


U3_SET_TARGET_CPU (avx2)
void
mod_avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TModAvx2CalcObj, cores::TCore, TPostProcessor, consts::size_core, consts::pxs_per_cycle > (info);
  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TAvx2CalcObj, cores::TCore, TPostProcessor, consts::size_core, consts::pxs_per_cycle > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::base::c5x5

#endif
