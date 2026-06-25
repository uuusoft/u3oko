/**
\file     dct_func_mmx.cpp
\date     23.03.2016
\author   Erashov Anton erashov2026@proton.me
\brief    MMX function IDCT coding, var1
*/
/**
\file       ???.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../codec-funcs-includes_int.hpp"
#include "dct_func_mmx_sse_sse2.h"

#ifdef U3_CPU_X86
//////////////////////////////////////////////////////////////////////////////
//
//  fdctmm32.c - AP922 MMX fDCT
//  ----------
//  Intel Application Note AP-922 - fast, precise implementation of DCT
//        http://developer.intel.com/vtune/cbts/appnotes.htm
//  ----------
//
//       This code will run on any MMX CPU.  The dct_row operation can be
//  further optimized using PentiumIII/Athlon instructions (pshufw.)
//  If the code will be run on a 3D-Now CPU (AMD K6-2/Athlon), a slight
//  accruacy-boost can be obtained.  Please see fdctam32.c for details.
//
//    For a fast, precise MMX implementation of inverse-DCT
//              visit http://www.elecard.com/peter
//              or check out Avery Lee's Virtualdub source-code
//                 http://www.concentric.net/~psilon
//
//  Revision history
//  ----------------
//
//  v1.01 08/ 26/ 2000 ( clipper bugfix )
//         In my haste to get this code out the door, I neglected to consider
//       the numerical range of output.  I *believe* an IEEE-1180/ 1990 fdct
//       is range-limited to {-2048, +2047}.
//       fdctmm32.c now saturates the output DCT coefficients to this range.
//         A few comment typos were corrected. Equivalent-C code for
//       the forward_dct column stage has also been added.  The pseudo-C
//       code in Intel's AP-922 omits several important operations that
//       would cause dct8_frw_col() to fail, if it were used directly without
//       modification.
//         There is still room for additional optimization in the
//       frw_dct_row_mmx() function.  The data pack/unpack operation could be
//       shortened with pshufw.
//
//  v1.0 07/ 20/ 2000 (initial release )
//       Initial release of AP922 MMX forward_DCT.
//
//
//  liaor@iname.com  http://members.tripod.com/~liaor
//////////////////////////////////////////////////////////////////////////////

namespace dlls::codecs::dct
{
#  define INP eax      // pointer to (short *codec_block)
#  define OUTL ecx     // pointer to output ( temporary store space qwTemp[] )
#  define TABLE ebx    // pointer to tab_frw_01234567[]
#  define TABLEF ebx   // pointer to tg_all_16
#  define round_frw_row edx

#  define x0 INP + 0 * 16
#  define x1 INP + 1 * 16
#  define x2 INP + 2 * 16
#  define x3 INP + 3 * 16
#  define x4 INP + 4 * 16
#  define x5 INP + 5 * 16
#  define x6 INP + 6 * 16
#  define x7 INP + 7 * 16
#  define y0 OUTL + 0 * 16
#  define y1 OUTL + 1 * 16
#  define y2 OUTL + 2 * 16
#  define y3 OUTL + 3 * 16
#  define y4 OUTL + 4 * 16
#  define y5 OUTL + 5 * 16
#  define y6 OUTL + 6 * 16
#  define y7 OUTL + 7 * 16

//////////////////////////////////////////////////////////////////////
//
// constants for the forward DCT
// -----------------------------
//
// Be sure to check that your compiler is aligning all constants to QWORD
// (8-byte ) memory boundaries!  Otherwise the unaligned memory access will
// severely stall MMX execution.
//
//////////////////////////////////////////////////////////////////////

#  define BITS_FRW_ACC 2   // 2 or 3 for accuracy
#  define SHIFT_FRW_COL BITS_FRW_ACC
#  define SHIFT_FRW_ROW (BITS_FRW_ACC + 17)

// v1.01 The original SHIFT_FRW_ROW constant has been replaced by a
//      "two stage" shift operation.  The 1st-shift (CLIP1 ) aligns the
//      intermediate 32-bit integer data to a {-32768, +32768} (16-bit word)
//      range.  The MMX instruction "packssdw" simultaneous clips and packs
//      the intermediate-data into 16-bit format.
//      The 2nd-shift (CLIP2 ) restores the proper final range {-2048,+2047}

#  define SHIFT_FRW_ROW_CLIP2 (4)   // 4-bit shift -> { 32768 <> 2048 }
#  define SHIFT_FRW_ROW_CLIP1 (SHIFT_FRW_ROW - SHIFT_FRW_ROW_CLIP2)

// #define RND_FRW_ROW   (262144 * (BITS_FRW_ACC - 1 ) ) //; 1 << (SHIFT_FRW_ROW-1 )
#  define RND_FRW_ROW (1 << (SHIFT_FRW_ROW - 1))
// #define RND_FRW_COL   (2 * (BITS_FRW_ACC - 1 ) ) //; 1 << (SHIFT_FRW_COL-1 )
#  define RND_FRW_COL (1 << (SHIFT_FRW_COL - 1))

U3_ALIGN_DEFAULT const static long long one_corr = 0x0001000100010001;
// const static long long __attribute__ ( aligned(16) ) one_corr = 0x0001000100010001;

const static long r_frw_row[2] = { RND_FRW_ROW, RND_FRW_ROW };

// concatenated table, for forward DCT-column transformation
U3_ALIGN_DEFAULT const static std::int16_t tg_all_16[] =
  // const static std::int16_t __attribute__ ( aligned(16) ) tg_all_16[] =
  {
    13036, 13036, 13036, 13036,   // tg * (2<<16) + 0.5
    27146,
    27146,
    27146,
    27146,   // tg * (2<<16) + 0.5
    -21746,
    -21746,
    -21746,
    -21746,   // tg * (2<<16) + 0.5
    -19195,
    -19195,
    -19195,
    -19195,   // cos * (2<<16) + 0.5
    23170,
    23170,
    23170,
    23170   // cos * (2<<15 ) + 0.5
  };

#  define tg_1_16 (TABLEF + 0)
#  define tg_2_16 (TABLEF + 8)
#  define tg_3_16 (TABLEF + 16)
#  define cos_4_16 (TABLEF + 24)
#  define ocos_4_16 (TABLEF + 32)


// forward_dct coeff table
static const std::int16_t tab_frw_01234567[] = {
  // row0
  16384,
  16384,
  21407,
  -8867,   //    w09 w01 w08 w00
  16384,
  16384,
  8867,
  -21407,   //    w13 w05 w12 w04
  16384,
  -16384,
  8867,
  21407,   //    w11 w03 w10 w02
  -16384,
  16384,
  -21407,
  -8867,   //    w15 w07 w14 w06
  22725,
  12873,
  19266,
  -22725,   //    w22 w20 w18 w16
  19266,
  4520,
  -4520,
  -12873,   //    w23 w21 w19 w17
  12873,
  4520,
  4520,
  19266,   //    w30 w28 w26 w24
  -22725,
  19266,
  -12873,
  -22725,   //    w31 w29 w27 w25

  // row1
  22725,
  22725,
  29692,
  -12299,   //    w09 w01 w08 w00
  22725,
  22725,
  12299,
  -29692,   //    w13 w05 w12 w04
  22725,
  -22725,
  12299,
  29692,   //    w11 w03 w10 w02
  -22725,
  22725,
  -29692,
  -12299,   //    w15 w07 w14 w06
  31521,
  17855,
  26722,
  -31521,   //    w22 w20 w18 w16
  26722,
  6270,
  -6270,
  -17855,   //    w23 w21 w19 w17
  17855,
  6270,
  6270,
  26722,   //    w30 w28 w26 w24
  -31521,
  26722,
  -17855,
  -31521,   //    w31 w29 w27 w25

  // row2
  21407,
  21407,
  27969,
  -11585,   //    w09 w01 w08 w00
  21407,
  21407,
  11585,
  -27969,   //    w13 w05 w12 w04
  21407,
  -21407,
  11585,
  27969,   //    w11 w03 w10 w02
  -21407,
  21407,
  -27969,
  -11585,   //    w15 w07 w14 w06
  29692,
  16819,
  25172,
  -29692,   //    w22 w20 w18 w16
  25172,
  5906,
  -5906,
  -16819,   //    w23 w21 w19 w17
  16819,
  5906,
  5906,
  25172,   //    w30 w28 w26 w24
  -29692,
  25172,
  -16819,
  -29692,   //    w31 w29 w27 w25

  // row3
  19266,
  19266,
  25172,
  -10426,   //    w09 w01 w08 w00
  19266,
  19266,
  10426,
  -25172,   //    w13 w05 w12 w04
  19266,
  -19266,
  10426,
  25172,   //    w11 w03 w10 w02
  -19266,
  19266,
  -25172,
  -10426,   //    w15 w07 w14 w06,
  26722,
  15137,
  22654,
  -26722,   //    w22 w20 w18 w16
  22654,
  5315,
  -5315,
  -15137,   //    w23 w21 w19 w17
  15137,
  5315,
  5315,
  22654,   //    w30 w28 w26 w24
  -26722,
  22654,
  -15137,
  -26722,   //    w31 w29 w27 w25,

  // row4
  16384,
  16384,
  21407,
  -8867,   //    w09 w01 w08 w00
  16384,
  16384,
  8867,
  -21407,   //    w13 w05 w12 w04
  16384,
  -16384,
  8867,
  21407,   //    w11 w03 w10 w02
  -16384,
  16384,
  -21407,
  -8867,   //    w15 w07 w14 w06
  22725,
  12873,
  19266,
  -22725,   //    w22 w20 w18 w16
  19266,
  4520,
  -4520,
  -12873,   //    w23 w21 w19 w17
  12873,
  4520,
  4520,
  19266,   //    w30 w28 w26 w24
  -22725,
  19266,
  -12873,
  -22725,   //    w31 w29 w27 w25

  // row5
  19266,
  19266,
  25172,
  -10426,   //    w09 w01 w08 w00
  19266,
  19266,
  10426,
  -25172,   //    w13 w05 w12 w04
  19266,
  -19266,
  10426,
  25172,   //    w11 w03 w10 w02
  -19266,
  19266,
  -25172,
  -10426,   //    w15 w07 w14 w06
  26722,
  15137,
  22654,
  -26722,   //    w22 w20 w18 w16
  22654,
  5315,
  -5315,
  -15137,   //    w23 w21 w19 w17
  15137,
  5315,
  5315,
  22654,   //    w30 w28 w26 w24
  -26722,
  22654,
  -15137,
  -26722,   //    w31 w29 w27 w25

  // row6
  21407,
  21407,
  27969,
  -11585,   //    w09 w01 w08 w00
  21407,
  21407,
  11585,
  -27969,   //    w13 w05 w12 w04
  21407,
  -21407,
  11585,
  27969,   //    w11 w03 w10 w02
  -21407,
  21407,
  -27969,
  -11585,   //    w15 w07 w14 w06,
  29692,
  16819,
  25172,
  -29692,   //    w22 w20 w18 w16
  25172,
  5906,
  -5906,
  -16819,   //    w23 w21 w19 w17
  16819,
  5906,
  5906,
  25172,   //    w30 w28 w26 w24
  -29692,
  25172,
  -16819,
  -29692,   //    w31 w29 w27 w25,

  // row7
  22725,
  22725,
  29692,
  -12299,   //    w09 w01 w08 w00
  22725,
  22725,
  12299,
  -29692,   //    w13 w05 w12 w04
  22725,
  -22725,
  12299,
  29692,   //    w11 w03 w10 w02
  -22725,
  22725,
  -29692,
  -12299,   //    w15 w07 w14 w06,
  31521,
  17855,
  26722,
  -31521,   //    w22 w20 w18 w16
  26722,
  6270,
  -6270,
  -17855,   //    w23 w21 w19 w17
  17855,
  6270,
  6270,
  26722,   //    w30 w28 w26 w24
  -31521,
  26722,
  -17855,
  -31521   //    w31 w29 w27 w25
};


void
FDCTransform8x8MMX (std::int16_t* codec_block)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  // long long xt70[2]; // xt7xt6xt5xt4, xt3xt2xt1xt0
  // int a0, a2, a3, b1, b2;
  // int b2;
  // std::int16_t *sptr, *optr, *tf; // tf = table_ptr
  // int j;

  const static std::int16_t tg_1_16   = 13036;    // tg * (2<<16) + 0.5
  const static std::int16_t tg_2_16   = 27146;    // tg * (2<<16) + 0.5
  const static std::int16_t tg_3_16   = -21746;   // tg * (2<<16) + 0.5
  const static std::int16_t cos_4_16  = -19195;   // cos * (2<<16) + 0.5
  const static std::int16_t ocos_4_16 = 23170;    // cos * (2<<15 ) + 0.5
  const static std::int16_t one_corr  = 1;        // rounding compensation

  // std::int16_t t0, t1, t3, t4, t5, t6;
  // std::int16_t tp03, tm03, tp12, tm12, tp65, tm65;
  // std::int16_t tm465, tm765;

  // std::int16_t *xt = (short *)&xt70[0];

  __asm {
    ////////////////////////////////////////////////////////////////////////
    //
    // The high-level pseudocode for the fdct_mm32() routine :
    //
    // fdct_mm32()
    // {
    //    forward_dct_col03(); // dct_column transform on cols 0-3
    //    forward_dct_col47(); // dct_column transform on cols 4-7
    //    for ( j = 0; j < 8; j=j+1 )
    //      forward_dct_row1(j); // dct_row transform on row #j
    // }

      mov INP, dword ptr[codec_block];;   // input data is row 0 of codec_block[] - transform the left half of the matrix (4 columns)

      lea TABLEF, dword ptr[tg_all_16];
      mov OUTL, INP;

    //  lea round_frw_col, dword ptr [r_frw_col]
    // for ( i = 0; i < 2; i = i + 1 )
    // the for-loop is executed twice.  We are better off unrolling the
    // loop to avoid branch misprediction.

    // mmx32_fdct_col03: // begin processing columns 0-3

      movq mm0, [x1]; 0; x1

      movq mm1, [x6]; 1; x6
      movq mm2, mm0; 2; x1

      movq mm3, [x2]; 3; x2
      paddsw mm0, mm1; t1 = x[1] + x[6]

      movq mm4, [x5]; 4; x5
      psllw mm0, SHIFT_FRW_COL; t1

      movq mm5, [x0]; 5; x0
      paddsw mm4, mm3; t2 = x[2] + x[5]

      paddsw mm5, [x7]; t0 = x[0] + x[7]
      psllw mm4, SHIFT_FRW_COL; t2

      movq mm6, mm0; 6; t1
      psubsw mm2, mm1; 1; t6 = x[1] - x[6]

      movq mm1, qword ptr[tg_2_16]; 1; tg_2_16
      psubsw mm0, mm4; tm12 = t1 - t2

      movq mm7, [x3]; 7; x3
      pmulhw mm1, mm0; tm12*tg_2_16

      paddsw mm7, [x4]; t3 = x[3] + x[4]
      psllw mm5, SHIFT_FRW_COL; t0

      paddsw mm6, mm4; 4; tp12 = t1 + t2
      psllw mm7, SHIFT_FRW_COL; t3

      movq mm4, mm5; 4; t0
      psubsw mm5, mm7; tm03 = t0 - t3

      paddsw mm1, mm5; y2 = tm03 + tm12*tg_2_16
      paddsw mm4, mm7; 7; tp03 = t0 + t3

      por mm1, qword ptr one_corr; correction y2 + 0.5
      psllw mm2, SHIFT_FRW_COL + 1; t6

      pmulhw mm5, qword ptr[tg_2_16]; tm03*tg_2_16
      movq mm7, mm4; 7; tp03

      psubsw mm3, [x5]; t5 = x[2] - x[5]
      psubsw mm4, mm6; y4 = tp03 - tp12

      movq[y2], mm1; 1; save y2
      paddsw mm7, mm6; 6; y0 = tp03 + tp12

      movq mm1, [x3]; 1; x3
      psllw mm3, SHIFT_FRW_COL + 1; t5;

      psubsw mm1, [x4]; t4 = x[3] - x[4];
      movq mm6, mm2; 6; t6;

      movq[y4], mm4; 4; save y4;
      paddsw mm2, mm3; t6 + t5;

      pmulhw mm2, qword ptr[ocos_4_16]; tp65 = ( t6 + t5 ) *cos_4_16;
      psubsw mm6, mm3; 3; t6 - t5;

      pmulhw mm6, qword ptr[ocos_4_16]; tm65 = ( t6 - t5 ) *cos_4_16;
      psubsw mm5, mm0; 0; y6 = tm03*tg_2_16 - tm12;

      por mm5, qword ptr one_corr; correction y6 + 0.5;
      psllw mm1, SHIFT_FRW_COL; t4;

      por mm2, qword ptr one_corr; correction tp65 + 0.5;
      movq mm4, mm1; 4; t4;

      movq mm3, [x0]; 3; x0;
      paddsw mm1, mm6; tp465 = t4 + tm65;

      psubsw mm3, [x7]; t7 = x[0] - x[7];
      psubsw mm4, mm6; 6; tm465 = t4 - tm65;

      movq mm0, qword ptr[tg_1_16]; 0; tg_1_16;
      psllw mm3, SHIFT_FRW_COL; t7;

      movq mm6, qword ptr[tg_3_16]; 6; tg_3_16;
      pmulhw mm0, mm1; tp465*tg_1_16;

      movq[y0], mm7; 7; save y0;
      pmulhw mm6, mm4; tm465*tg_3_16;

      movq[y6], mm5; 5; save y6;
      movq mm7, mm3; 7; t7;

      movq mm5, qword ptr[tg_3_16]; 5; tg_3_16;
      psubsw mm7, mm2; tm765 = t7 - tp65;

      paddsw mm3, mm2; 2; tp765 = t7 + tp65;
      pmulhw mm5, mm7; tm765*tg_3_16;

      paddsw mm0, mm3; y1 = tp765 + tp465*tg_1_16;
      paddsw mm6, mm4; tm465*tg_3_16;

      pmulhw mm3, qword ptr[tg_1_16]; tp765*tg_1_16;

      por mm0, qword ptr one_corr; correction y1 + 0.5;
      paddsw mm5, mm7; tm765*tg_3_16;

      psubsw mm7, mm6; 6; y3 = tm765 - tm465*tg_3_16;
      add INP, 0x08;   // increment pointer;

      movq[y1], mm0; 0; save y1;
      paddsw mm5, mm4; 4; y5 = tm765*tg_3_16 + tm465;

      movq[y3], mm7; 7; save y3;
      psubsw mm3, mm1; 1; y7 = tp765*tg_1_16 - tp465;

      movq[y5], mm5; 5; save y5;

    // mmx32_fdct_col47: // begin processing columns 4-7;

      movq mm0, [x1]; 0; x1;
      movq[y7], mm3; 3; save y7 ( columns 0 - 4 );

      movq mm1, [x6]; 1; x6;
      movq mm2, mm0; 2; x1;

      movq mm3, [x2]; 3; x2;
      paddsw mm0, mm1; t1 = x[1] + x[6];

      movq mm4, [x5]; 4; x5;
      psllw mm0, SHIFT_FRW_COL; t1;

      movq mm5, [x0]; 5; x0;
      paddsw mm4, mm3; t2 = x[2] + x[5];

      paddsw mm5, [x7]; t0 = x[0] + x[7];
      psllw mm4, SHIFT_FRW_COL; t2;

      movq mm6, mm0; 6; t1;
      psubsw mm2, mm1; 1; t6 = x[1] - x[6];

      movq mm1, qword ptr[tg_2_16]; 1; tg_2_16;
      psubsw mm0, mm4; tm12 = t1 - t2;

      movq mm7, [x3]; 7; x3;
      pmulhw mm1, mm0; tm12*tg_2_16;

      paddsw mm7, [x4]; t3 = x[3] + x[4];
      psllw mm5, SHIFT_FRW_COL; t0;

      paddsw mm6, mm4; 4; tp12 = t1 + t2;
      psllw mm7, SHIFT_FRW_COL; t3;

      movq mm4, mm5; 4; t0;
      psubsw mm5, mm7; tm03 = t0 - t3;

      paddsw mm1, mm5; y2 = tm03 + tm12*tg_2_16;
      paddsw mm4, mm7; 7; tp03 = t0 + t3;

      por mm1, qword ptr one_corr; correction y2 + 0.5;
      psllw mm2, SHIFT_FRW_COL + 1; t6;

      pmulhw mm5, qword ptr[tg_2_16]; tm03*tg_2_16;
      movq mm7, mm4; 7; tp03;

      psubsw mm3, [x5]; t5 = x[2] - x[5];
      psubsw mm4, mm6; y4 = tp03 - tp12;

      movq[y2 + 8], mm1; 1; save y2;
      paddsw mm7, mm6; 6; y0 = tp03 + tp12;

      movq mm1, [x3]; 1; x3;
      psllw mm3, SHIFT_FRW_COL + 1; t5;

      psubsw mm1, [x4]; t4 = x[3] - x[4];
      movq mm6, mm2; 6; t6;

      movq[y4 + 8], mm4; 4; save y4;
      paddsw mm2, mm3; t6 + t5;

      pmulhw mm2, qword ptr[ocos_4_16]; tp65 = ( t6 + t5 ) *cos_4_16;
      psubsw mm6, mm3; 3; t6 - t5;

      pmulhw mm6, qword ptr[ocos_4_16]; tm65 = ( t6 - t5 ) *cos_4_16;
      psubsw mm5, mm0; 0; y6 = tm03*tg_2_16 - tm12;

      por mm5, qword ptr one_corr; correction y6 + 0.5;
      psllw mm1, SHIFT_FRW_COL; t4;

      por mm2, qword ptr one_corr; correction tp65 + 0.5;
      movq mm4, mm1; 4; t4;

      movq mm3, [x0]; 3; x0;
      paddsw mm1, mm6; tp465 = t4 + tm65;

      psubsw mm3, [x7]; t7 = x[0] - x[7];
      psubsw mm4, mm6; 6; tm465 = t4 - tm65;

      movq mm0, qword ptr[tg_1_16]; 0; tg_1_16;
      psllw mm3, SHIFT_FRW_COL; t7;

      movq mm6, qword ptr[tg_3_16]; 6; tg_3_16;
      pmulhw mm0, mm1; tp465*tg_1_16;

      movq[y0 + 8], mm7; 7; save y0;
      pmulhw mm6, mm4; tm465*tg_3_16;

      movq[y6 + 8], mm5; 5; save y6;
      movq mm7, mm3; 7; t7;

      movq mm5, qword ptr[tg_3_16]; 5; tg_3_16;
      psubsw mm7, mm2; tm765 = t7 - tp65;

      paddsw mm3, mm2; 2; tp765 = t7 + tp65;
      pmulhw mm5, mm7; tm765*tg_3_16;

      paddsw mm0, mm3; y1 = tp765 + tp465*tg_1_16;
      paddsw mm6, mm4; tm465*tg_3_16;

      pmulhw mm3, qword ptr[tg_1_16]; tp765*tg_1_16;

      por mm0, qword ptr one_corr; correction y1 + 0.5;
      paddsw mm5, mm7; tm765*tg_3_16;

      psubsw mm7, mm6; 6; y3 = tm765 - tm465*tg_3_16;

      movq[y1 + 8], mm0; 0; save y1;
      paddsw mm5, mm4; 4; y5 = tm765*tg_3_16 + tm465;

      movq[y3 + 8], mm7; 7; save y3;
      psubsw mm3, mm1; 1; y7 = tp765*tg_1_16 - tp465;

      movq[y5 + 8], mm5; 5; save y5;

      movq[y7 + 8], mm3; 3; save y7;

    // end of forward_dct_col07()
    // done with dct_col transform

    ////////////////////////////////////////////////////////////////////////
    //
    // fdct_mmx32_rows() --
    // the following subroutine performs the row-transform operation,
    //
    //  The output is stored into codec_block[], destroying the original
    //  source data.
    //  v1.01 - output is range-clipped to {-2048, +2047}

      mov INP, dword ptr[codec_block];;   // row 0;
      mov edi, 0x08;   // x = 8;

      lea TABLE, dword ptr[tab_frw_01234567];   // row 0;
      mov OUTL, INP;

      lea round_frw_row, dword ptr[r_frw_row];
    // for ( x = 8; x > 0; --x )  // transform 1 row per iteration;

    // ---------- loop begin
      lp_mmx_fdct_row1:

      movd mm5, dword ptr[INP + 12];   // mm5 = 7 6;

      punpcklwd mm5, dword ptr[INP + 8]   // mm5 =  5 7 4 6;

      movq mm2, mm5;   // mm2 = 5 7 4 6;
      psrlq mm5, 32;   // mm5 = _ _ 5 7;

      movq mm0, qword ptr[INP];   // mm0 = 3 2 1 0;
      punpcklwd mm5, mm2;   // mm5 = 4 5 6 7;

      movq mm1, mm0;   // mm1 = 3 2 1 0;
      paddsw mm0, mm5;   // mm0 = [3+4, 2+5, 1+6, 0+7] ( xt3, xt2, xt1, xt0);

      psubsw mm1, mm5;   // mm1 = [3-4, 2-5, 1-6, 0-7] ( xt7, xt6, xt5, xt4 );
      movq mm2, mm0;   // mm2 = [ xt3 xt2 xt1 xt0 ];

      punpcklwd mm0, mm1;   // mm0 = [ xt5 xt1 xt4 xt0 ];

      punpckhwd mm2, mm1;   // mm2 = [ xt7 xt3 xt6 xt2 ];
      movq mm1, mm2;   // mm1;

    // shuffle bytes around;
      movq mm2, mm0; 2; x3 x2 x1 x0;

      movq mm3, qword ptr[TABLE]; 3; w06 w04 w02 w00;
      punpcklwd mm0, mm1; x5 x1 x4 x0;

      movq mm5, mm0; 5; x5 x1 x4 x0;
      punpckldq mm0, mm0; x4 x0 x4 x0[xt2 xt0 xt2 xt0];

      movq mm4, qword ptr[TABLE + 8]; 4; w07 w05 w03 w01;
      punpckhwd mm2, mm1; 1; x7 x3 x6 x2;

      pmaddwd mm3, mm0; x4*w06 + x0*w04 x4*w02 + x0*w00;
      movq mm6, mm2; 6; x7 x3 x6 x2;

      movq mm1, qword ptr[TABLE + 32]; 1; w22 w20 w18 w16;
      punpckldq mm2, mm2; x6 x2 x6 x2[xt3 xt1 xt3 xt1];

      pmaddwd mm4, mm2; x6*w07 + x2*w05 x6*w03 + x2*w01;
      punpckhdq mm5, mm5; x5 x1 x5 x1[xt6 xt4 xt6 xt4];

      pmaddwd mm0, qword ptr[TABLE + 16]; x4*w14 + x0*w12 x4*w10 + x0*w08;
      punpckhdq mm6, mm6; x7 x3 x7 x3[xt7 xt5 xt7 xt5];

      movq mm7, qword ptr[TABLE + 40]; 7; w23 w21 w19 w17;
      pmaddwd mm1, mm5; x5*w22 + x1*w20 x5*w18 + x1*w16;

    // mm3 = a1, a0 (y2,y0);
    // mm1 = b1, b0 (y3,y1 );
    // mm0 = a3,a2  (y6,y4 );
    // mm5 = b3,b2  (y7,y5 );

      paddd mm3, qword ptr[round_frw_row]; +rounder (y2, y0);
      pmaddwd mm7, mm6; x7*w23 + x3*w21 x7*w19 + x3*w17;

      pmaddwd mm2, qword ptr[TABLE + 24]; x6*w15 + x2*w13 x6*w11 + x2*w09;
      paddd mm3, mm4; 4; a1 = sum (even1 ) a0 = sum (even0)   // now ( y2, y0);

      pmaddwd mm5, qword ptr[TABLE + 48]; x5*w30 + x1*w28 x5*w26 + x1*w24;

      pmaddwd mm6, qword ptr[TABLE + 56]; x7*w31 + x3*w29 x7*w27 + x3*w25;
      paddd mm1, mm7; 7; b1 = sum (odd1 ) b0 = sum (odd0)   // now ( y3, y1 );

      paddd mm0, qword ptr[round_frw_row]; +rounder (y6, y4 );
      psrad mm3, SHIFT_FRW_ROW_CLIP1;   // (y2, y0);

      paddd mm1, qword ptr[round_frw_row]; +rounder (y3, y1 );
      paddd mm0, mm2; 2; a3 = sum (even3) a2 = sum (even2 )   // now (y6, y4 );

      paddd mm5, qword ptr[round_frw_row]; +rounder (y7, y5 );
      psrad mm1, SHIFT_FRW_ROW_CLIP1;   // y1=a1+b1 y0=a0+b0;

      paddd mm5, mm6; 6; b3 = sum (odd3) b2 = sum (odd2 )   // now ( y7, y5 );
      psrad mm0, SHIFT_FRW_ROW_CLIP1;   // y3=a3+b3 y2=a2+b2;

      add OUTL, 16;   // increment row-output address by 1 row;
      psrad mm5, SHIFT_FRW_ROW_CLIP1;   // y4=a3-b3 y5=a2-b2;

      add INP, 16;   // increment row-address by 1 row;
      packssdw mm3, mm0;   // 0; y6 y4 y2 y0, saturate {-32768,+32767};

      packssdw mm1, mm5;   // 3; y7 y5 y3 y1, saturate {-32768,+32767};
      movq mm6, mm3;   // mm0 = y6 y4 y2 y0;

      punpcklwd mm3, mm1;   // y3 y2 y1 y0;
      sub edi, 0x01;   // i = i - 1;

      punpckhwd mm6, mm1;   // y7 y6 y5 y4;
      add TABLE, 64;   // increment to next table;

      psraw mm3, SHIFT_FRW_ROW_CLIP2;   // descale [y3 y2 y1 y0] to {-2048,+2047};

      psraw mm6, SHIFT_FRW_ROW_CLIP2;   // descale [y7 y6 y5 y4] to {-2048,+2047};

      movq qword ptr[OUTL - 16], mm3; 1; save y3 y2 y1 y0;

      movq qword ptr[OUTL - 8], mm6; 7; save y7 y6 y5 y4;

      cmp edi, 0x00;
      jg lp_mmx_fdct_row1;   // begin fdct processing on next row;
      emms;
  }
#  endif
  /*
    ////////////////////////////////////////////////////////////////////////
    //
    // DCT_8_FRW_COL(), equivalent c_code
    //
    // This C-code can be substituted for the same __asm block
    //
    // I found several *DISCREPANCIES* between the AP-922 C-listing
    // and actual corrected code (shown below).
    //
    ////////////////////////////////////////////////////////////////////////

    sptr = (short *) codec_block;
    optr = (short *) codec_block; // output will overwrite source data!

    for ( j = 0; j < 8; j=j+1 ) // dct_frw_col1 loop
    {
    // read source-data column #j into xt[0..7]
    xt[7] = sptr[7*8];
    xt[6] = sptr[6*8];
    xt[5] = sptr[5*8];
    xt[4] = sptr[4*8];

    xt[3] = sptr[3*8];
    xt[2] = sptr[2*8];
    xt[1] = sptr[1*8];
    xt[0] = sptr[0*8];

    #define  LEFT_SHIFT( x ) ( ( x ) << (SHIFT_FRW_COL) )   // left shift
    #define LEFT_SHIFT1( x ) ( ( x ) << (SHIFT_FRW_COL+1 ) ) // left shift+1

    t0 = LEFT_SHIFT ( xt[0] + xt[7] );
    t1 = LEFT_SHIFT ( xt[1] + xt[6] );
    t2 = LEFT_SHIFT ( xt[2] + xt[5] );
    t3 = LEFT_SHIFT ( xt[3] + xt[4] );
    t4 = LEFT_SHIFT ( xt[3] - xt[4] );
    t5 = LEFT_SHIFT1( xt[2] - xt[5] ); // *** DISCREPANCY
    t6 = LEFT_SHIFT1( xt[1] - xt[6] ); // *** DISCREPANCY
    t7 = LEFT_SHIFT ( xt[0] - xt[7] );

    tp03 = t0 + t3;
    tm03 = t0 - t3;
    tp12 = t1 + t2;
    tm12 = t1 - t2;

    // pmulhw/pmulhrw emulation macros
    #define X86_PMULHW( X ) ( (std::int16_t) ( ( (int )X)>>16 ) )   //Intel MMX

    optr[0*8] = tp03 + tp12;
    optr[4*8] = tp03 - tp12;
    optr[2*8] = tm03 + X86_PMULHW( tm12 * tg_2_16 );
    optr[2*8] = optr[2*8] | one_corr; // one_correction
    optr[6*8] = X86_PMULHW( tm03 * tg_2_16 ) - tm12;
    optr[6*8] = optr[6*8] | one_corr; // one_correction

    tp65 = X86_PMULHW( ( t6 +t5 ) *ocos_4_16 ); // *** DISCREPANCY
    tp65 = tp65 | one_corr; // one_correction
    tm65 = X86_PMULHW( ( t6 -t5 ) *ocos_4_16 ); // *** DISCREPANCY

    tp765 = t7 + tp65;
    tm765 = t7 - tp65;
    tp465 = t4 + tm65;
    tm465 = t4 - tm65;

    optr[1*8]  = tp765 + X86_PMULHW( tp465 * tg_1_16 );
    optr[1*8]  = optr[1*8] | one_corr; // one_correction
    optr[7*8] = X86_PMULHW( tp765 * tg_1_16 ) - tp465;

    //optr[5*8] = X86_PMULHW( tm765 * tg_3_16 ) + tm465; // *** DISCREPANCY
    // from pg8 of AP-922,  ICONST = [ const*(2^16) + 0.5 ]
    //                      const * x = PMULHW( ICONST,x ) + x
    // The constant "tg_3_16" > 0.5, thus tg_3_16 is encoded as tg_3_16-1.0
    // optr[5*8] = X86_PMULHW( tm765 * ( tg_3_16 - 1.0 ) ) + tm465
    //           = [tm765*tg_3_16 - tm765] + tm465
    //
    // optr[5*8] + tm765 = [ tm765*tg_3_16 ] + tm465 + tm765
    //                   = [ tm765*tg_3_16 ] + tm465 <-- what we want

    optr[5*8] = X86_PMULHW( tm765 * tg_3_16 ) + tm465 + tm765;

    //optr[3*8] = tm765 - X86_PMULHW( tm465 * tg_3_16 ); // *** DISCREPANCY
    // The following operations must be performed in the shown order!
    // same trick ( as shown for optr[5*8] ) applies to optr[3*8]

    optr[3*8] = X86_PMULHW( tm465 * tg_3_16 ) + tm465;
    optr[3*8] = tm765 - optr[3*8];

    ++sptr;   // increment source pointer +1 column
    ++optr;   // increment output pointer +1 column
    } // end for ( j = 0 ..., end of C_equivalent code for forward_dct_col_1

    ////////////////////////////////////////////////////////////////////////
    //
    // DCT8_FRW_ROW1(), equivalent c_code
    //
    // This C-code can be substituted for the same __asm block
    // For a derivation of this code, please read fdctmm32.doc
    ////////////////////////////////////////////////////////////////////////

    sptr = (short *) codec_block;
    optr = (short *) codec_block; // output will overwrite source data!
    tf = &tab_frw_01234567[ 0 ]; // fdct_row load table_forward_w

    for ( j = 0; j < 8; j=j+1 ) // dct_frw_row1 loop
    {
    // forward_dct_row input arithmetic + shuffle
    xt[3] = sptr[3] + sptr[4];
    xt[2] = sptr[2] + sptr[5];
    xt[1] = sptr[1] + sptr[6];
    xt[0] = sptr[0] + sptr[7];

    xt[7] = sptr[3] - sptr[4];
    xt[6] = sptr[2] - sptr[5];
    xt[5] = sptr[1] - sptr[6];
    xt[4] = sptr[0] - sptr[7];

    a3 = ( xt[0]*tf[10]+ xt[2]*tf[11] ) + ( xt[1]*tf[14]+ xt[3]*tf[15] );
    a2 = ( xt[0]*tf[8] + xt[2]*tf[9] ) + ( xt[1]*tf[12]+ xt[3]*tf[13] );
    a1 = ( xt[0]*tf[2] + xt[2]*tf[3] ) + ( xt[1]*tf[6] + xt[3]*tf[7] );
    a0 = ( xt[0]*tf[0] + xt[2]*tf[1] ) + ( xt[1]*tf[4] + xt[3]*tf[5] );
    tf += 16;  // increment table pointer

    b3 = ( xt[4]*tf[10]+ xt[6]*tf[11] ) + ( xt[5]*tf[14]+ xt[7]*tf[15] );
    b2 = ( xt[4]*tf[8] + xt[6]*tf[9] ) + ( xt[5]*tf[12]+ xt[7]*tf[13] );
    b1 = ( xt[4]*tf[2] + xt[6]*tf[3] ) + ( xt[5]*tf[6] + xt[7]*tf[7] );
    b0 = ( xt[4]*tf[0] + xt[6]*tf[1] ) + ( xt[5]*tf[4] + xt[7]*tf[5] );
    tf += 16;  // increment table pointer

    // apply rounding constants to scaled elements
    // note, in the MMX implementation, the shift&round is done *last.*
    // Here, the C-code applies the shifts 1st, then the clipping.
    #define SHIFT_AND_ROUND_FRW_ROW( x )  ( ( ( x )+RND_FRW_ROW) >> SHIFT_FRW_ROW )

    a3 = SHIFT_AND_ROUND_FRW_ROW( a3 );
    a2 = SHIFT_AND_ROUND_FRW_ROW( a2 );
    a1 = SHIFT_AND_ROUND_FRW_ROW( a1 );
    a0 = SHIFT_AND_ROUND_FRW_ROW( a0 );

    b3 = SHIFT_AND_ROUND_FRW_ROW( b3 );
    b2 = SHIFT_AND_ROUND_FRW_ROW( b2 );
    b1 = SHIFT_AND_ROUND_FRW_ROW( b1 );
    b0 = SHIFT_AND_ROUND_FRW_ROW( b0 );

    // v1.01, clip output results to range {-2048, +2047}

    // In the MMX implementation, the "clipper" is integrated into
    // the shift&round operation ( thanks to packssdw)
    a3 = ( a3 > 2047) ?  2047 : a3; // ceiling @ +2047
    a2 = ( a2 > 2047) ?  2047 : a2; // ceiling @ +2047
    a1 = ( a1 > 2047) ?  2047 : a1; // ceiling @ +2047
    a0 = ( a0 > 2047) ?  2047 : a0; // ceiling @ +2047
    b3 = (b3 > 2047) ?  2047 : b3; // ceiling @ +2047
    b2 = (b2 > 2047) ?  2047 : b2; // ceiling @ +2047
    b1 = (b1 > 2047) ?  2047 : b1; // ceiling @ +2047
    b0 = (b0 > 2047) ?  2047 : b0; // ceiling @ +2047

    a3 = ( a3 <-2048) ? -2048 : a3; // floor   @ -2048
    a2 = ( a2 <-2048) ? -2048 : a2; // floor   @ -2048
    a1 = ( a1 <-2048) ? -2048 : a1; // floor   @ -2048
    a0 = ( a0 <-2048) ? -2048 : a0; // floor   @ -2048
    b3 = (b3 <-2048) ? -2048 : b3; // floor   @ -2048
    b2 = (b2 <-2048) ? -2048 : b2; // floor   @ -2048
    b1 = (b1 <-2048) ? -2048 : b1; // floor   @ -2048
    b0 = (b0 <-2048) ? -2048 : b0; // floor   @ -2048

    // forward_dct_row, assign outputs
    optr[ 3 ] = b1;
    optr[ 2 ] = a1;
    optr[ 1 ] = b0;
    optr[ 0 ] = a0;

    optr[ 7 ] = b3;
    optr[ 6 ] = a3;
    optr[ 5 ] = b2;
    optr[ 4 ] = a2;

    sptr += 8;   // increment source pointer +1 row
    optr += 8;   // increment output pointer +1 row
    } // end for ( j = 0 ..., end of C_equivalent code for forward_dct_row_1
    */
};

#  undef INP
#  undef OUTL
#  undef TABLE
#  undef TABLEF
#  undef round_frw_row

#  undef x0
#  undef x1
#  undef x2
#  undef x3
#  undef x4
#  undef x5
#  undef x6
#  undef x7
#  undef y0
#  undef y1
#  undef y2
#  undef y3
#  undef y4
#  undef y5
#  undef y6
#  undef y7

#  undef BITS_FRW_ACC
#  undef SHIFT_FRW_COL
#  undef SHIFT_FRW_ROW

#  undef SHIFT_FRW_ROW_CLIP2
#  undef SHIFT_FRW_ROW_CLIP1

#  undef RND_FRW_ROW
#  undef RND_FRW_COL

#  undef tg_1_16
#  undef tg_2_16
#  undef tg_3_16
#  undef cos_4_16
#  undef ocos_4_16

//////////////////////////////////////////////////////////////////////////////
/**************************************************************************
 *                                                                        *
 * This code is developed by John Funnell.  This software is an           *
 * an implementation of a part of one or more MPEG-4 Video tools as       *
 * specified in ISO/IEC 14496-2 standard.  Those intending to use this    *
 * software module in hardware or software products are advised that its  *
 * use may infringe existing patents or copyrights, and any such use      *
 * would be at such party's own risk.  The original developer of this     *
 * software module and his/her company, and subsequent editors and their  *
 * companies (including Project Mayo), will have no liability for use of  *
 * this software or modifications or derivatives thereof.                 *
 *                                                                        *
 * Project Mayo gives users of the Codec a license to this software       *
 * module or modifications thereof for use in hardware or software        *
 * products claiming conformance to the MPEG-4 Video Standard as          *
 * described in the Open DivX license.                                    *
 *                                                                        *
 * The complete Open DivX license can be found at                         *
 * http://www.projectmayo.com/opendivx/license.php .                      *
 *                                                                        *
 **************************************************************************/

/**************************************************************************
 *
 *  text_idct_mmx.c
 *
 *  Copyright (C) 2001  Project Mayo
 *
 *  John Funnell
 *
 *  DivX Advance Research Center <darc@projectmayo.com>
 *
 **************************************************************************/

/* This file contains idct functions with MMX optimization.               */
/* Please see acknowledgement below.                                      */

/*
;
; MMX iDCT
;
; Originally provided by Intel at AP-922
; http://developer.intel.com/vtune/cbts/strmsimd/922down.htm
; (See more app notes at http://developer.intel.com/vtune/cbts/strmsimd/appnotes.htm)
; but in a limited edition.
; New macro implements a column part for precise iDCT
; The routine precision now satisfies IEEE standard 1180-1990.
;
; Copyright ( c) 2000-2001 Peter Gubanov <peter@elecard.net.ru>
; Rounding trick Copyright ( c) 2000 Michel Lespinasse <walken@zoy.org>
;
; http://www.elecard.com/peter/idct.html
; http://www.linuxvideo.org/mpeg2dec/
;
; Conversion to MS-style inline C format ( c) 2001 Project Mayo Inc. John Funnell
;
; Version v1.0.0 10 January 2001
;
*/


/*
 if you are not setting the name of you MMX idct function with compile flag MMX_IDCT_NAME,
 then you need to choose a name to insert in here:
 */


/* some conversions from readable integer constants to qwords */
#  define SHORT4_TO_QWORD(A, B, C, D) (                  \
    ((((uint64_t) (A)) & ((uint64_t) (0xffff))) << 0) |  \
    ((((uint64_t) (B)) & ((uint64_t) (0xffff))) << 16) | \
    ((((uint64_t) (C)) & ((uint64_t) (0xffff))) << 32) | \
    ((((uint64_t) (D)) & ((uint64_t) (0xffff))) << 48))

#  define INT2_TO_QWORD(A, B) (                             \
    ((((uint64_t) (A)) & ((uint64_t) (0xffffffff))) << 0) | \
    ((((uint64_t) (B)) & ((uint64_t) (0xffffffff))) << 32))


#  define BITS_INV_ACC 5 /* 4 or 5 for IEEE */
#  define SHIFT_INV_ROW (16 - BITS_INV_ACC)
#  define SHIFT_INV_COL (1 + BITS_INV_ACC)
#  define RND_INV_ROW (1024 * (6 - BITS_INV_ACC)) /* 1 << (SHIFT_INV_ROW-1 ) */
#  define RND_INV_COL (16 * (BITS_INV_ACC - 3))   /* 1 << (SHIFT_INV_COL-1 ) */
#  define RND_INV_CORR (RND_INV_COL - 1)          /* correction -1.0 and round */
#  define BITS_FRW_ACC 3                          /* 2 or 3 for accuracy */
#  define SHIFT_FRW_COL BITS_FRW_ACC
#  define SHIFT_FRW_ROW (BITS_FRW_ACC + 17)
#  define RND_FRW_ROW (262144 * (BITS_FRW_ACC - 1)) /* 1 << (SHIFT_FRW_ROW-1 ) */


/* rounding value that is added before the row transform's rounding */


#  if SHIFT_INV_ROW == 12
static const std::uint64_t rounder[8] = {
  INT2_TO_QWORD (65536, 65536), /* rounder_0 */
  INT2_TO_QWORD (7195, 7195),   /* rounder_1 */
  INT2_TO_QWORD (4520, 4520),   /* rounder_2 */
  INT2_TO_QWORD (2407, 2407),   /* rounder_3 */
  INT2_TO_QWORD (0, 0),         /* rounder_4 */
  INT2_TO_QWORD (240, 240),     /* rounder_5 */
  INT2_TO_QWORD (1024, 1024),   /* rounder_6 */
  INT2_TO_QWORD (1024, 1024)    /* rounder_7 */
};
#  elif SHIFT_INV_ROW == 11
static const std::uint64_t rounder[2 * 8] = {
  INT2_TO_QWORD (65536, 65536), /* rounder_0 */
  INT2_TO_QWORD (3597, 3597),   /* rounder_1 */
  INT2_TO_QWORD (2260, 2260),   /* rounder_2 */
  INT2_TO_QWORD (1203, 1203),   /* rounder_3 */
  INT2_TO_QWORD (0, 0),         /* rounder_4 */
  INT2_TO_QWORD (120, 120),     /* rounder_5 */
  INT2_TO_QWORD (512, 512),     /* rounder_6 */
  INT2_TO_QWORD (512, 512)      /* rounder_7 */
};
#  endif


/*
  ;=============================================================================
  ;
  ; The first stage iDCT 8x8 - inverse DCTs of rows
  ;
  ;-----------------------------------------------------------------------------
  ; The 8-point inverse DCT direct algorithm
  ;-----------------------------------------------------------------------------
  ;
  ; static const std::int16_t w[32] = {
  ; FIX( cos_4_16), FIX( cos_2_16), FIX( cos_4_16), FIX( cos_6_16),
  ; FIX( cos_4_16), FIX( cos_6_16), -FIX( cos_4_16), -FIX( cos_2_16),
  ; FIX( cos_4_16), -FIX( cos_6_16), -FIX( cos_4_16), FIX( cos_2_16),
  ; FIX( cos_4_16), -FIX( cos_2_16), FIX( cos_4_16), -FIX( cos_6_16),
  ; FIX( cos_1_16), FIX( cos_3_16), FIX( cos_5_16), FIX( cos_7_16),
  ; FIX( cos_3_16), -FIX( cos_7_16), -FIX( cos_1_16), -FIX( cos_5_16),
  ; FIX( cos_5_16), -FIX( cos_1_16), FIX( cos_7_16), FIX( cos_3_16),
  ; FIX( cos_7_16), -FIX( cos_5_16), FIX( cos_3_16), -FIX( cos_1_16) };
  ;
  ; #define DCT_8_INV_ROW( x, y)
  ;{
  ; int a0, a1, a2, a3, b0, b1, b2, b3;
  ;
  ; a0 =x[0]*w[0]+x[2]*w[1]+x[4]*w[2]+x[6]*w[3];
  ; a1 =x[0]*w[4]+x[2]*w[5]+x[4]*w[6]+x[6]*w[7];
  ; a2 = x[0] * w[ 8] + x[2] * w[ 9] + x[4] * w[10] + x[6] * w[11];
  ; a3 = x[0] * w[12] + x[2] * w[13] + x[4] * w[14] + x[6] * w[15];
  ; b0 = x[1] * w[16] + x[3] * w[17] + x[5] * w[18] + x[7] * w[19];
  ; b1 = x[1] * w[20] + x[3] * w[21] + x[5] * w[22] + x[7] * w[23];
  ; b2 = x[1] * w[24] + x[3] * w[25] + x[5] * w[26] + x[7] * w[27];
  ; b3 = x[1] * w[28] + x[3] * w[29] + x[5] * w[30] + x[7] * w[31];
  ;
  ; y[0] = SHIFT_ROUND ( a0 + b0 );
  ; y[1] = SHIFT_ROUND ( a1 + b1 );
  ; y[2] = SHIFT_ROUND ( a2 + b2 );
  ; y[3] = SHIFT_ROUND ( a3 + b3 );
  ; y[4] = SHIFT_ROUND ( a3 - b3 );
  ; y[5] = SHIFT_ROUND ( a2 - b2 );
  ; y[6] = SHIFT_ROUND ( a1 - b1 );
  ; y[7] = SHIFT_ROUND ( a0 - b0 );
  ;}
  ;
  ;-----------------------------------------------------------------------------
  ;
  ; In this implementation the outputs of the iDCT-1D are multiplied
  ; for rows 0,4 - by cos_4_16,
  ; for rows 1,7 - by cos_1_16,
  ; for rows 2,6 - by cos_2_16,
  ; for rows 3,5 - by cos_3_16
  ; and are shifted to the left for better accuracy
  ;
  ; For the constants used,
  ; FIX(float_const ) = (std::int16_t) (float_const * (1<<15 ) + 0.5 )
  ;
  ;=============================================================================
  */


/*
  ;=============================================================================
  ; code for MMX
  ;=============================================================================
  ; Table for rows 0,4 - constants are multiplied by cos_4_16
  */
static const std::uint64_t tab_i_04[8 * 8] = {
  /* Table for rows 0,4 - constants are multiplied by cos_4_16 */
  SHORT4_TO_QWORD (16384, 16384, 16384, -16384),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (21407, 8867, 8867, -21407),     /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (16384, -16384, 16384, 16384),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-8867, 21407, -21407, -8867),   /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (22725, 12873, 19266, -22725),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (19266, 4520, -4520, -12873),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (12873, 4520, 4520, 19266),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-22725, 19266, -12873, -22725), /*        w31 w29 w27 w25 */
  /* Table for rows 1,7 - constants are multiplied by cos_1_16 */
  SHORT4_TO_QWORD (22725, 22725, 22725, -22725),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (29692, 12299, 12299, -29692),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (22725, -22725, 22725, 22725),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-12299, 29692, -29692, -12299), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (31521, 17855, 26722, -31521),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (26722, 6270, -6270, -17855),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (17855, 6270, 6270, 26722),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-31521, 26722, -17855, -31521), /*        w31 w29 w27 w25 */
  /* Table for rows 2,6 - constants are multiplied by cos_2_16 */
  SHORT4_TO_QWORD (21407, 21407, 21407, -21407),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (27969, 11585, 11585, -27969),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (21407, -21407, 21407, 21407),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-11585, 27969, -27969, -11585), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (29692, 16819, 25172, -29692),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (25172, 5906, -5906, -16819),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (16819, 5906, 5906, 25172),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-29692, 25172, -16819, -29692), /*        w31 w29 w27 w25 */
  /* Table for rows 3,5 - constants are multiplied by cos_3_16 */
  SHORT4_TO_QWORD (19266, 19266, 19266, -19266),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (25172, 10426, 10426, -25172),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (19266, -19266, 19266, 19266),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-10426, 25172, -25172, -10426), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (26722, 15137, 22654, -26722),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (22654, 5315, -5315, -15137),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (15137, 5315, 5315, 22654),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-26722, 22654, -15137, -26722), /*        w31 w29 w27 w25 */
  /* Table for rows 0,4 - constants are multiplied by cos_4_16 */
  SHORT4_TO_QWORD (16384, 16384, 16384, -16384),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (21407, 8867, 8867, -21407),     /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (16384, -16384, 16384, 16384),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-8867, 21407, -21407, -8867),   /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (22725, 12873, 19266, -22725),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (19266, 4520, -4520, -12873),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (12873, 4520, 4520, 19266),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-22725, 19266, -12873, -22725), /*        w31 w29 w27 w25 */
  /* Table for rows 3,5 - constants are multiplied by cos_3_16 */
  SHORT4_TO_QWORD (19266, 19266, 19266, -19266),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (25172, 10426, 10426, -25172),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (19266, -19266, 19266, 19266),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-10426, 25172, -25172, -10426), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (26722, 15137, 22654, -26722),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (22654, 5315, -5315, -15137),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (15137, 5315, 5315, 22654),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-26722, 22654, -15137, -26722), /*        w31 w29 w27 w25 */
  /* Table for rows 2,6 - constants are multiplied by cos_2_16 */
  SHORT4_TO_QWORD (21407, 21407, 21407, -21407),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (27969, 11585, 11585, -27969),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (21407, -21407, 21407, 21407),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-11585, 27969, -27969, -11585), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (29692, 16819, 25172, -29692),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (25172, 5906, -5906, -16819),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (16819, 5906, 5906, 25172),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-29692, 25172, -16819, -29692), /*        w31 w29 w27 w25 */
  /* Table for rows 1,7 - constants are multiplied by cos_1_16 */
  SHORT4_TO_QWORD (22725, 22725, 22725, -22725),   /* movq-> w06 w04 w02 w00 */
  SHORT4_TO_QWORD (29692, 12299, 12299, -29692),   /*        w07 w05 w03 w01 */
  SHORT4_TO_QWORD (22725, -22725, 22725, 22725),   /*        w14 w12 w10 w08 */
  SHORT4_TO_QWORD (-12299, 29692, -29692, -12299), /*        w15 w13 w11 w09 */
  SHORT4_TO_QWORD (31521, 17855, 26722, -31521),   /*        w22 w20 w18 w16 */
  SHORT4_TO_QWORD (26722, 6270, -6270, -17855),    /*        w23 w21 w19 w17 */
  SHORT4_TO_QWORD (17855, 6270, 6270, 26722),      /*        w30 w28 w26 w24 */
  SHORT4_TO_QWORD (-31521, 26722, -17855, -31521), /*        w31 w29 w27 w25 */
};


#  define INP eax
#  define ROUNDER ebx
#  define TABLE ecx
#  define OUTP edx

void
IDCTransform8x8MMX (std::int16_t* block)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else

  static const std::uint64_t tg_1_16   = SHORT4_TO_QWORD (13036, 13036, 13036, 13036);
  static const std::uint64_t tg_2_16   = SHORT4_TO_QWORD (27146, 27146, 27146, 27146);
  static const std::uint64_t tg_3_16   = SHORT4_TO_QWORD (-21746, -21746, -21746, -21746);
  static const std::uint64_t ocos_4_16 = SHORT4_TO_QWORD (23170, 23170, 23170, 23170);

  std::uint64_t tempMatrix[64 / 4];

  __asm {
      push eax;
      push ebx;
      push ecx;
      push edx;
      push edi;

      mov INP, block;
      lea OUTP, [tempMatrix];
      lea TABLE, [tab_i_04];
      lea ROUNDER, [rounder];

      mov edi, -8;; i = -8;

      align 16;

      rowloop:

      movq mm0, qword ptr[INP]; 0; x3 x2 x1 x0;

      movq mm1, qword ptr[INP + 8]; 1; x7 x6 x5 x4;
      movq mm2, mm0; 2; x3 x2 x1 x0;

      movq mm3, qword ptr[TABLE]; 3; w06 w04 w02 w00;
      punpcklwd mm0, mm1; x5 x1 x4 x0;

      movq mm5, mm0; 5; x5 x1 x4 x0;
      punpckldq mm0, mm0; x4 x0 x4 x0;

      movq mm4, qword ptr[TABLE + 8]; 4; w07 w05 w03 w01;
      punpckhwd mm2, mm1; 1; x7 x3 x6 x2;

      pmaddwd mm3, mm0; x4*w06 + x0*w04 x4*w02 + x0*w00;
      movq mm6, mm2; 6; x7 x3 x6 x2;

      movq mm1, qword ptr[TABLE + 32]; 1; w22 w20 w18 w16;
      punpckldq mm2, mm2; x6 x2 x6 x2;

      pmaddwd mm4, mm2; x6*w07 + x2*w05 x6*w03 + x2*w01;
      punpckhdq mm5, mm5; x5 x1 x5 x1;

      pmaddwd mm0, qword ptr[TABLE + 16]; x4*w14 + x0*w12 x4*w10 + x0*w08;
      punpckhdq mm6, mm6; x7 x3 x7 x3;

      movq mm7, qword ptr[TABLE + 40]; 7; w23 w21 w19 w17;
      pmaddwd mm1, mm5; x5*w22 + x1*w20 x5*w18 + x1*w16;

      paddd mm3, qword ptr[ROUNDER]; +rounder;
      pmaddwd mm7, mm6; x7*w23 + x3*w21 x7*w19 + x3*w17;

      pmaddwd mm2, qword ptr[TABLE + 24]; x6*w15 + x2*w13 x6*w11 + x2*w09;
      paddd mm3, mm4; 4; a1 = sum (even1 ) a0 = sum (even0);

      pmaddwd mm5, qword ptr[TABLE + 48]; x5*w30 + x1*w28 x5*w26 + x1*w24;
      movq mm4, mm3; 4; a1 a0;

      pmaddwd mm6, qword ptr[TABLE + 56]; x7*w31 + x3*w29 x7*w27 + x3*w25;
      paddd mm1, mm7; 7; b1 = sum (odd1 ) b0 = sum (odd0);

      paddd mm0, qword ptr[ROUNDER]; +rounder;
      psubd mm3, mm1; a1 - b1 a0 - b0;

      psrad mm3, SHIFT_INV_ROW; y6 = a1 - b1 y7 = a0 - b0;
      paddd mm1, mm4; 4; a1 + b1 a0 + b0;

      paddd mm0, mm2; 2; a3 = sum (even3) a2 = sum (even2 );
      psrad mm1, SHIFT_INV_ROW; y1 = a1 + b1 y0 = a0 + b0;

      paddd mm5, mm6; 6; b3 = sum (odd3) b2 = sum (odd2 );
      movq mm4, mm0; 4; a3 a2;

      paddd mm0, mm5; a3 + b3 a2 + b2;
      psubd mm4, mm5; 5; a3 - b3 a2 - b2;

      psrad mm0, SHIFT_INV_ROW; y3 = a3 + b3 y2 = a2 + b2;
      psrad mm4, SHIFT_INV_ROW; y4 = a3 - b3 y5 = a2 - b2;

      packssdw mm1, mm0; 0; y3 y2 y1 y0;
      packssdw mm4, mm3; 3; y6 y7 y4 y5;

      movq mm7, mm4; 7; y6 y7 y4 y5;
      psrld mm4, 16; 0 y6 0 y4;

      pslld mm7, 16; y7 0 y5 0;
      movq qword ptr[OUTP], mm1; 1; save y3 y2 y1 y0;

      por mm7, mm4; 4; y7 y6 y5 y4;
      movq qword ptr[OUTP + 8], mm7; 7; save y7 y6 y5 y4;

      add INP, 16; add 1 row to input pointer;
      add ROUNDER, 8; go to next rounding values;
      add OUTP, 16; add 1 row to output pointer;
      add TABLE, 64; move to next section of table;

      add edi, 1;
      jne rowloop;

    /* column code starts here... */

      lea INP, [tempMatrix];
      mov OUTP, block;
      mov edi, -2;; i = -2;

      align 16;

      colloop:

      movq  mm0, tg_3_16;

      movq  mm3, qword ptr[INP + 16 * 3];
      movq  mm1, mm0; tg_3_16;

      movq  mm5, qword ptr[INP + 16 * 5];
      pmulhw  mm0, mm3; x3*( tg_3_16 - 1 );

      movq  mm4, tg_1_16;
      pmulhw  mm1, mm5; x5*( tg_3_16 - 1 );

      movq  mm7, qword ptr[INP + 16 * 7];
      movq  mm2, mm4; tg_1_16;

      movq  mm6, qword ptr[INP + 16 * 1];
      pmulhw  mm4, mm7; x7*tg_1_16;

      paddsw  mm0, mm3; x3*tg_3_16;
      pmulhw  mm2, mm6; x1*tg_1_16;

      paddsw  mm1, mm3; x3 + x5*( tg_3_16 - 1 );
      psubsw  mm0, mm5; x3*tg_3_16 - x5 = tm35;

      movq  mm3, ocos_4_16;
      paddsw  mm1, mm5; x3 + x5*tg_3_16 = tp35;

      paddsw  mm4, mm6; x1 + tg_1_16*x7 = tp17;
      psubsw  mm2, mm7; x1*tg_1_16 - x7 = tm17;

      movq  mm5, mm4; tp17;
      movq  mm6, mm2; tm17;

      paddsw  mm5, mm1; tp17 + tp35 = b0;
      psubsw  mm6, mm0; tm17 - tm35 = b3;

      psubsw  mm4, mm1; tp17 - tp35 = t1;
      paddsw  mm2, mm0; tm17 + tm35 = t2;

      movq  mm7, tg_2_16;
      movq  mm1, mm4; t1;

      movq  qword ptr[OUTP + 3 * 16], mm5; save b0;
      paddsw  mm1, mm2; t1 + t2;

      movq  qword ptr[OUTP + 5 * 16], mm6; save b3;
      psubsw  mm4, mm2; t1 - t2;

      movq  mm5, qword ptr[INP + 2 * 16];
      movq  mm0, mm7; tg_2_16;

      movq  mm6, qword ptr[INP + 6 * 16];
      pmulhw  mm0, mm5; x2*tg_2_16;

      pmulhw  mm7, mm6; x6*tg_2_16;
      ; slot;
      pmulhw  mm1, mm3; ocos_4_16*( t1 + t2 ) = b1 / 2;
      ; slot;
      movq  mm2, qword ptr[INP + 0 * 16];
      pmulhw  mm4, mm3; ocos_4_16*( t1 - t2 ) = b2 / 2;

      psubsw  mm0, mm6; t2*tg_2_16 - x6 = tm26;
      movq  mm3, mm2; x0;

      movq  mm6, qword ptr[INP + 4 * 16];
      paddsw  mm7, mm5; x2 + x6*tg_2_16 = tp26;

      paddsw  mm2, mm6; x0 + x4 = tp04;
      psubsw  mm3, mm6; x0 - x4 = tm04;

      movq  mm5, mm2; tp04;
      movq  mm6, mm3; tm04;

      psubsw  mm2, mm7; tp04 - tp26 = a3;
      paddsw  mm3, mm0; tm04 + tm26 = a1;

      paddsw mm1, mm1; b1;
      paddsw mm4, mm4; b2;

      paddsw  mm5, mm7; tp04 + tp26 = a0;
      psubsw  mm6, mm0; tm04 - tm26 = a2;

      movq  mm7, mm3; a1;
      movq  mm0, mm6; a2;

      paddsw  mm3, mm1; a1 + b1;
      paddsw  mm6, mm4; a2 + b2;

      psraw mm3, SHIFT_INV_COL; dst1;
      psubsw  mm7, mm1; a1 - b1;

      psraw mm6, SHIFT_INV_COL; dst2;
      psubsw  mm0, mm4; a2 - b2;

      movq  mm1, qword ptr[OUTP + 3 * 16]; load b0;
      psraw mm7, SHIFT_INV_COL; dst6;

      movq  mm4, mm5; a0;
      psraw mm0, SHIFT_INV_COL; dst5;

      movq  qword ptr[OUTP + 1 * 16], mm3;
      paddsw  mm5, mm1; a0 + b0;

      movq  qword ptr[OUTP + 2 * 16], mm6;
      psubsw  mm4, mm1; a0 - b0;

      movq  mm3, qword ptr[OUTP + 5 * 16]; load b3;
      psraw mm5, SHIFT_INV_COL; dst0;

      movq  mm6, mm2; a3;
      psraw mm4, SHIFT_INV_COL; dst7;

      movq  qword ptr[OUTP + 5 * 16], mm0;
      paddsw  mm2, mm3; a3 + b3;

      movq  qword ptr[OUTP + 6 * 16], mm7;
      psubsw  mm6, mm3; a3 - b3;

      movq  qword ptr[OUTP + 0 * 16], mm5;
      psraw mm2, SHIFT_INV_COL; dst3;

      movq  qword ptr[OUTP + 7 * 16], mm4;
      psraw mm6, SHIFT_INV_COL; dst4;

      movq  qword ptr[OUTP + 3 * 16], mm2;
      movq  qword ptr[OUTP + 4 * 16], mm6;

      lea INP, [tempMatrix];
      mov OUTP, block;
      add INP, 8; add 4 cols to input pointer;
      add OUTP, 8; add 4 cols to output pointer;

      add edi, 1;
      jne colloop;

      pop edi;
      pop edx;
      pop ecx;
      pop ebx;
      pop eax;

      emms;
  }
#  endif
}
}   // namespace dlls::codecs::dct
#endif
