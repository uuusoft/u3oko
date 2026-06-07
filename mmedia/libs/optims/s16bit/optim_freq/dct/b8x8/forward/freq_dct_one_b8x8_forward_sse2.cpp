/**
\file       freq_dct_one_b8x8_forward_sse2.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
#  define CONST_BITS 8   //; 14 is also OK.

#  if 0
%if CONST_BITS == 8
F_0_382 equ      98             //; FIX(0.382683433)
F_0_541 equ     139             //; FIX(0.541196100)
F_0_707 equ     181             //; FIX(0.707106781 )
F_1_306 equ     334             //; FIX(1.306562965 )
%else
//; NASM cannot do compile-time arithmetic on floating-point constants.
%define DESCALE( x,n)  ( ( ( x )+(1<<( (n)-1 ) ) )>>(n) )
F_0_382 equ     DESCALE( 410903207,30-CONST_BITS)       //; FIX(0.382683433)
F_0_541 equ     DESCALE( 581104887,30-CONST_BITS)       //; FIX(0.541196100)
F_0_707 equ     DESCALE( 759250124,30-CONST_BITS)       //; FIX(0.707106781 )
F_1_306 equ     DESCALE(1402911301,30-CONST_BITS)       //; FIX(1.306562965 )
%endif

#  endif

//; PRE_MULTIPLY_SCALE_BITS <= 2 ( to avoid overflow)
//; CONST_BITS + CONST_SHIFT + PRE_MULTIPLY_SCALE_BITS == 16 (for _mm_mulhi_epi16)

#  define PRE_MULTIPLY_SCALE_BITS 2
#  define CONST_SHIFT (16 - PRE_MULTIPLY_SCALE_BITS - CONST_BITS)

#  if 0
PW_F0707        times 8 dw  F_0_707 << CONST_SHIFT
PW_F0382        times 8 dw  F_0_382 << CONST_SHIFT
PW_F0541        times 8 dw  F_0_541 << CONST_SHIFT
PW_F1306        times 8 dw  F_1_306 << CONST_SHIFT

%define data(b )         (b )+8           //; DCTELEM *data

%define original_ebp    ebp+0
%define wk(i)           ebp-(WK_NUM-(i) ) *SIZEOF_XMMWORD //; xmmword wk[WK_NUM]
%define WK_NUM          2
#  endif

U3_SET_TARGET_CPU (sse2)
void
sse2_b8x8 (std::int16_t* buf)
{
  __m128i       _xmm0;
  __m128i       _xmm1;
  __m128i       _xmm2;
  __m128i       _xmm3;
  __m128i       _xmm4;
  __m128i       _xmm5;
  __m128i       _xmm6;
  __m128i       _xmm7;
  __m128i       _wk0;
  __m128i       _wk1;
  const __m128i _PW_F0382 = _mm_set1_epi16 (98);
  const __m128i _PW_F0541 = _mm_set1_epi16 (139);
  const __m128i _PW_F0707 = _mm_set1_epi16 (181);
  const __m128i _PW_F1306 = _mm_set1_epi16 (334);


  //; ---- Pass 1: process rows.

  _xmm0 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 0 * 8));
  _xmm1 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 1 * 8));
  _xmm2 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 2 * 8));
  _xmm3 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 3 * 8));

  //; _xmm0=(00 01 02 03 04 05 06 07), _xmm2=(20 21 22 23 24 25 26 27)
  //; _xmm1=(10 11 12 13 14 15 16 17), _xmm3=( 30 31 32 33 34 35 36 37)

  _xmm4 = _xmm0;                               //; transpose coefficients(phase 1 )
  _xmm0 = _mm_unpacklo_epi16 (_xmm0, _xmm1);   //; _xmm0=(00 10 01 11 02 12 03 13)
  _xmm4 = _mm_unpackhi_epi16 (_xmm4, _xmm1);   //; _xmm4=(04 14 05 15 06 16 07 17)
  _xmm5 = _xmm2;                               //; transpose coefficients(phase 1 )
  _xmm2 = _mm_unpacklo_epi16 (_xmm2, _xmm3);   //; _xmm2=(20 30 21 31 22 32 23 33)
  _xmm5 = _mm_unpackhi_epi16 (_xmm5, _xmm3);   //; _xmm5=(24 34 25 35 26 36 27 37)

  _xmm6 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 4 * 8));
  _xmm7 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 5 * 8));
  _xmm1 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 6 * 8));
  _xmm3 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 7 * 8));

  //; _xmm6=( 4 12 20 28 36 44 52 60), _xmm1=( 6 14 22 30 38 46 54 62 )
  //; _xmm7=( 5 13 21 29 37 45 53 61 ), _xmm3=( 7 15 23 31 39 47 55 63)

  _wk0 = _xmm2;   //; wk(0)=(20 30 21 31 22 32 23 33)
  _wk1 = _xmm5;   //; wk(1 )=(24 34 25 35 26 36 27 37)

  _xmm2 = _xmm6;                               //; transpose coefficients(phase 1 )
  _xmm6 = _mm_unpacklo_epi16 (_xmm6, _xmm7);   //; _xmm6=(40 50 41 51 42 52 43 53)
  _xmm2 = _mm_unpackhi_epi16 (_xmm2, _xmm7);   //; _xmm2=(44 54 45 55 46 56 47 57)
  _xmm5 = _xmm1;                               //; transpose coefficients(phase 1 )
  _xmm1 = _mm_unpacklo_epi16 (_xmm1, _xmm3);   //; _xmm1=( 60 70 61 71 62 72 63 73)
  _xmm5 = _mm_unpackhi_epi16 (_xmm5, _xmm3);   //; _xmm5=( 64 74 65 75 66 76 67 77)

  _xmm7 = _xmm6;                               //; transpose coefficients(phase 2 )
  _xmm6 = _mm_unpacklo_epi32 (_xmm6, _xmm1);   //; _xmm6=(40 50 60 70 41 51 61 71 )
  _xmm7 = _mm_unpackhi_epi32 (_xmm7, _xmm1);   //; _xmm7=(42 52 62 72 43 53 63 73)
  _xmm3 = _xmm2;                               //; transpose coefficients(phase 2 )
  _xmm2 = _mm_unpacklo_epi32 (_xmm2, _xmm5);   //; _xmm2=(44 54 64 74 45 55 65 75 )
  _xmm3 = _mm_unpackhi_epi32 (_xmm3, _xmm5);   //; _xmm3=(46 56 66 76 47 57 67 77)

  _xmm1 = _wk0;    //; _xmm1=(20 30 21 31 22 32 23 33)
  _xmm5 = _wk1;    //; _xmm5=(24 34 25 35 26 36 27 37)
  _wk0  = _xmm7;   //; _wk0=(42 52 62 72 43 53 63 73)
  _wk1  = _xmm2;   //; _wk1=(44 54 64 74 45 55 65 75 )

  _xmm7 = _xmm0;                               //; transpose coefficients(phase 2 )
  _xmm0 = _mm_unpacklo_epi32 (_xmm0, _xmm1);   //; _xmm0=(00 10 20 30 01 11 21 31 )
  _xmm7 = _mm_unpackhi_epi32 (_xmm7, _xmm1);   //; _xmm7=(02 12 22 32 03 13 23 33)
  _xmm2 = _xmm4;                               //; transpose coefficients(phase 2 )
  _xmm4 = _mm_unpacklo_epi32 (_xmm4, _xmm5);   //; _xmm4=(04 14 24 34 05 15 25 35 )
  _xmm2 = _mm_unpackhi_epi32 (_xmm2, _xmm5);   //; _xmm2=(06 16 26 36 07 17 27 37)

  _xmm1 = _xmm0;                               //; transpose coefficients(phase 3)
  _xmm0 = _mm_unpacklo_epi64 (_xmm0, _xmm6);   //; _xmm0=(00 10 20 30 40 50 60 70)=data0
  _xmm1 = _mm_unpackhi_epi64 (_xmm1, _xmm6);   //; _xmm1=(01 11 21 31 41 51 61 71 )=data1
  _xmm5 = _xmm2;                               //; transpose coefficients(phase 3)
  _xmm2 = _mm_unpacklo_epi64 (_xmm2, _xmm3);   //; _xmm2=(06 16 26 36 46 56 66 76)=data6
  _xmm5 = _mm_unpackhi_epi64 (_xmm5, _xmm3);   //; _xmm5=(07 17 27 37 47 57 67 77)=data7

  _xmm6 = _xmm1;
  _xmm3 = _xmm0;
  _xmm1 = _mm_sub_epi16 (_xmm1, _xmm2);   //; _xmm1=data1-data6=tmp6
  _xmm0 = _mm_sub_epi16 (_xmm0, _xmm5);   //; _xmm0=data0-data7=tmp7
  _xmm6 = _mm_add_epi16 (_xmm6, _xmm2);   //; _xmm6=data1+data6=tmp1
  _xmm3 = _mm_add_epi16 (_xmm3, _xmm5);   //; _xmm3=data0+data7=tmp0

  _xmm2 = _wk0;    //; _xmm2=(42 52 62 72 43 53 63 73)
  _xmm5 = _wk1;    //; _xmm5=(44 54 64 74 45 55 65 75 )
  _wk0  = _xmm1;   //; wk(0)=tmp6
  _wk1  = _xmm0;   //; wk(1 )=tmp7

  _xmm1 = _xmm7;                               //; transpose coefficients(phase 3)
  _xmm7 = _mm_unpacklo_epi64 (_xmm7, _xmm2);   //; _xmm7=(02 12 22 32 42 52 62 72 )=data2
  _xmm1 = _mm_unpackhi_epi64 (_xmm1, _xmm2);   //; _xmm1=(03 13 23 33 43 53 63 73)=data3
  _xmm0 = _xmm4;                               //; transpose coefficients(phase 3)
  _xmm4 = _mm_unpacklo_epi64 (_xmm4, _xmm5);   //; _xmm4=(04 14 24 34 44 54 64 74 )=data4
  _xmm0 = _mm_unpackhi_epi64 (_xmm0, _xmm5);   //; _xmm0=(05 15 25 35 45 55 65 75 )=data5

  _xmm2 = _xmm1;
  _xmm5 = _xmm7;
  _xmm1 = _mm_add_epi16 (_xmm1, _xmm4);   //; _xmm1=data3+data4=tmp3
  _xmm7 = _mm_add_epi16 (_xmm7, _xmm0);   //; _xmm7=data2+data5=tmp2
  _xmm2 = _mm_sub_epi16 (_xmm2, _xmm4);   //; _xmm2=data3-data4=tmp4
  _xmm5 = _mm_sub_epi16 (_xmm5, _xmm0);   //; _xmm5=data2-data5=tmp5

  //; -- Even part

  _xmm4 = _xmm3;
  _xmm0 = _xmm6;
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm1);   //; _xmm3=tmp13
  _xmm6 = _mm_sub_epi16 (_xmm6, _xmm7);   //; _xmm6=tmp12
  _xmm4 = _mm_add_epi16 (_xmm4, _xmm1);   //; _xmm4=tmp10
  _xmm0 = _mm_add_epi16 (_xmm0, _xmm7);   //; _xmm0=tmp11

  _xmm6 = _mm_add_epi16 (_xmm6, _xmm3);

  _xmm6 = _mm_slli_epi16 (_xmm6, PRE_MULTIPLY_SCALE_BITS);
  _xmm6 = _mm_mulhi_epi16 (_xmm6, _PW_F0707);   //; _xmm6=z1

  _xmm1 = _xmm4;
  _xmm7 = _xmm3;
  _xmm4 = _mm_sub_epi16 (_xmm4, _xmm0);   //; _xmm4=data4
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm6);   //; _xmm3=data6
  _xmm1 = _mm_add_epi16 (_xmm1, _xmm0);   //; _xmm1=data0
  _xmm7 = _mm_add_epi16 (_xmm7, _xmm6);   //; _xmm7=data2

  _xmm0 = _wk0;    //; _xmm0=tmp6
  _xmm6 = _wk1;    //; _xmm6=tmp7
  _wk0  = _xmm4;   //; wk(0)=data4
  _wk1  = _xmm3;   //; wk(1 )=data6

  //; -- Odd part

  _xmm2 = _mm_add_epi16 (_xmm2, _xmm5);   //; _xmm2=tmp10
  _xmm5 = _mm_add_epi16 (_xmm5, _xmm0);   //; _xmm5=tmp11
  _xmm0 = _mm_add_epi16 (_xmm0, _xmm6);   //; _xmm0=tmp12, _xmm6=tmp7

  _xmm2 = _mm_slli_epi16 (_xmm2, PRE_MULTIPLY_SCALE_BITS);
  _xmm0 = _mm_slli_epi16 (_xmm0, PRE_MULTIPLY_SCALE_BITS);

  _xmm5 = _mm_slli_epi16 (_xmm5, PRE_MULTIPLY_SCALE_BITS);
  _xmm5 = _mm_mulhi_epi16 (_xmm5, _PW_F0707);   //; _xmm5=z3
  _xmm4 = _xmm2;                                //; _xmm4=tmp10
  _xmm2 = _mm_sub_epi16 (_xmm2, _xmm0);
  _xmm2 = _mm_mulhi_epi16 (_xmm2, _PW_F0382);   //; _xmm2=z5
  _xmm4 = _mm_mulhi_epi16 (_xmm4, _PW_F0541);   //; _xmm4=MULTIPLY( tmp10,FIX_0_541196)
  _xmm0 = _mm_mulhi_epi16 (_xmm0, _PW_F1306);   //; _xmm0=MULTIPLY( tmp12,FIX_1_306562 )

  _xmm4 = _mm_add_epi16 (_xmm4, _xmm2);   //; _xmm4=z2
  _xmm0 = _mm_add_epi16 (_xmm0, _xmm2);   //; _xmm0=z4

  _xmm3 = _xmm6;
  _xmm6 = _mm_sub_epi16 (_xmm6, _xmm5);   //; _xmm6=z13
  _xmm3 = _mm_add_epi16 (_xmm3, _xmm5);   //; _xmm3=z11

  _xmm2 = _xmm6;
  _xmm5 = _xmm3;
  _xmm6 = _mm_sub_epi16 (_xmm6, _xmm4);   //; _xmm6=data3
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm0);   //; _xmm3=data7
  _xmm2 = _mm_add_epi16 (_xmm2, _xmm4);   //; _xmm2=data5
  _xmm5 = _mm_add_epi16 (_xmm5, _xmm0);   //; _xmm5=data1

  //; ---- Pass 2: process columns.

  //;       mov     edx, POINTER [data(eax )]        //; (DCTELEM *)

  //; _xmm1=(00 10 20 30 40 50 60 70), _xmm7=(02 12 22 32 42 52 62 72 )
  //; _xmm5=(01 11 21 31 41 51 61 71 ), _xmm6=(03 13 23 33 43 53 63 73)

  _xmm4 = _xmm1;                               //; transpose coefficients(phase 1 )
  _xmm1 = _mm_unpacklo_epi16 (_xmm1, _xmm5);   //; _xmm1=(00 01 10 11 20 21 30 31 )
  _xmm4 = _mm_unpackhi_epi16 (_xmm4, _xmm5);   //; _xmm4=(40 41 50 51 60 61 70 71 )
  _xmm0 = _xmm7;                               //; transpose coefficients(phase 1 )
  _xmm7 = _mm_unpacklo_epi16 (_xmm7, _xmm6);   //; _xmm7=(02 03 12 13 22 23 32 33)
  _xmm0 = _mm_unpackhi_epi16 (_xmm0, _xmm6);   //; _xmm0=(42 43 52 53 62 63 72 73)

  _xmm5 = _wk0;   //; _xmm5=col4
  _xmm6 = _wk1;   //; _xmm6=col6

  //; _xmm5=(04 14 24 34 44 54 64 74 ), _xmm6=(06 16 26 36 46 56 66 76)
  //; _xmm2=(05 15 25 35 45 55 65 75 ), _xmm3=(07 17 27 37 47 57 67 77)

  _wk0 = _xmm7;   //; wk(0)=(02 03 12 13 22 23 32 33)
  _wk1 = _xmm0;   //; wk(1 )=(42 43 52 53 62 63 72 73)

  _xmm7 = _xmm5;                               //; transpose coefficients(phase 1 )
  _xmm5 = _mm_unpacklo_epi16 (_xmm5, _xmm2);   //; _xmm5=(04 05 14 15 24 25 34 35 )
  _xmm7 = _mm_unpackhi_epi16 (_xmm7, _xmm2);   //; _xmm7=(44 45 54 55 64 65 74 75 )
  _xmm0 = _xmm6;                               //; transpose coefficients(phase 1 )
  _xmm6 = _mm_unpacklo_epi16 (_xmm6, _xmm3);   //; _xmm6=(06 07 16 17 26 27 36 37)
  _xmm0 = _mm_unpackhi_epi16 (_xmm0, _xmm3);   //; _xmm0=(46 47 56 57 66 67 76 77)

  _xmm2 = _xmm5;                               //; transpose coefficients(phase 2 )
  _xmm5 = _mm_unpacklo_epi32 (_xmm5, _xmm6);   //; _xmm5=(04 05 06 07 14 15 16 17)
  _xmm2 = _mm_unpackhi_epi32 (_xmm2, _xmm6);   //; _xmm2=(24 25 26 27 34 35 36 37)
  _xmm3 = _xmm7;                               //; transpose coefficients(phase 2 )
  _xmm7 = _mm_unpacklo_epi32 (_xmm7, _xmm0);   //; _xmm7=(44 45 46 47 54 55 56 57)
  _xmm3 = _mm_unpackhi_epi32 (_xmm3, _xmm0);   //; _xmm3=( 64 65 66 67 74 75 76 77)

  _xmm6 = _wk0;    //; _xmm6=(02 03 12 13 22 23 32 33)
  _xmm0 = _wk1;    //; _xmm0=(42 43 52 53 62 63 72 73)
  _wk0  = _xmm2;   //; wk(0)=(24 25 26 27 34 35 36 37)
  _wk1  = _xmm7;   //; wk(1 )=(44 45 46 47 54 55 56 57)

  _xmm2 = _xmm1;                               //; transpose coefficients(phase 2 )
  _xmm1 = _mm_unpacklo_epi32 (_xmm1, _xmm6);   //; _xmm1=(00 01 02 03 10 11 12 13)
  _xmm2 = _mm_unpackhi_epi32 (_xmm2, _xmm6);   //; _xmm2=(20 21 22 23 30 31 32 33)
  _xmm7 = _xmm4;                               //; transpose coefficients(phase 2 )
  _xmm4 = _mm_unpacklo_epi32 (_xmm4, _xmm0);   //; _xmm4=(40 41 42 43 50 51 52 53)
  _xmm7 = _mm_unpackhi_epi32 (_xmm7, _xmm0);   //; _xmm7=( 60 61 62 63 70 71 72 73)

  _xmm6 = _xmm1;                               //; transpose coefficients(phase 3)
  _xmm1 = _mm_unpacklo_epi64 (_xmm1, _xmm5);   //; _xmm1=(00 01 02 03 04 05 06 07)=data0
  _xmm6 = _mm_unpackhi_epi64 (_xmm6, _xmm5);   //; _xmm6=(10 11 12 13 14 15 16 17)=data1
  _xmm0 = _xmm7;                               //; transpose coefficients(phase 3)
  _xmm7 = _mm_unpacklo_epi64 (_xmm7, _xmm3);   //; _xmm7=( 60 61 62 63 64 65 66 67)=data6
  _xmm0 = _mm_unpackhi_epi64 (_xmm0, _xmm3);   //; _xmm0=(70 71 72 73 74 75 76 77)=data7

  _xmm5 = _xmm6;
  _xmm3 = _xmm1;
  _xmm6 = _mm_sub_epi16 (_xmm6, _xmm7);   //; _xmm6=data1-data6=tmp6
  _xmm1 = _mm_sub_epi16 (_xmm1, _xmm0);   //; _xmm1=data0-data7=tmp7
  _xmm5 = _mm_add_epi16 (_xmm5, _xmm7);   //; _xmm5=data1+data6=tmp1
  _xmm3 = _mm_add_epi16 (_xmm3, _xmm0);   //; _xmm3=data0+data7=tmp0

  _xmm7 = _wk0;    //; _xmm7=(24 25 26 27 34 35 36 37)
  _xmm0 = _wk1;    //; _xmm0=(44 45 46 47 54 55 56 57)
  _wk0  = _xmm6;   //; wk(0)=tmp6
  _wk1  = _xmm1;   //; wk(1 )=tmp7

  _xmm6 = _xmm2;                               //; transpose coefficients(phase 3)
  _xmm2 = _mm_unpacklo_epi64 (_xmm2, _xmm7);   //; _xmm2=(20 21 22 23 24 25 26 27)=data2
  _xmm6 = _mm_unpackhi_epi64 (_xmm6, _xmm7);   //; _xmm6=( 30 31 32 33 34 35 36 37)=data3
  _xmm1 = _xmm4;                               //; transpose coefficients(phase 3)
  _xmm4 = _mm_unpacklo_epi64 (_xmm4, _xmm0);   //; _xmm4=(40 41 42 43 44 45 46 47)=data4
  _xmm1 = _mm_unpackhi_epi64 (_xmm1, _xmm0);   //; _xmm1=(50 51 52 53 54 55 56 57)=data5

  _xmm7 = _xmm6;
  _xmm0 = _xmm2;
  _xmm6 = _mm_add_epi16 (_xmm6, _xmm4);   //; _xmm6=data3+data4=tmp3
  _xmm2 = _mm_add_epi16 (_xmm2, _xmm1);   //; _xmm2=data2+data5=tmp2
  _xmm7 = _mm_sub_epi16 (_xmm7, _xmm4);   //; _xmm7=data3-data4=tmp4
  _xmm0 = _mm_sub_epi16 (_xmm0, _xmm1);   //; _xmm0=data2-data5=tmp5

  //; -- Even part

  _xmm4 = _xmm3;
  _xmm1 = _xmm5;
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm6);   //; _xmm3=tmp13
  _xmm5 = _mm_sub_epi16 (_xmm5, _xmm2);   //; _xmm5=tmp12
  _xmm4 = _mm_add_epi16 (_xmm4, _xmm6);   //; _xmm4=tmp10
  _xmm1 = _mm_add_epi16 (_xmm1, _xmm2);   //; _xmm1=tmp11

  _xmm5 = _mm_add_epi16 (_xmm5, _xmm3);
  _xmm5 = _mm_slli_epi16 (_xmm5, PRE_MULTIPLY_SCALE_BITS);
  _xmm5 = _mm_mulhi_epi16 (_xmm5, _PW_F0707);   //; _xmm5=z1

  _xmm6 = _xmm4;
  _xmm2 = _xmm3;
  _xmm4 = _mm_sub_epi16 (_xmm4, _xmm1);   //; _xmm4=data4
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm5);   //; _xmm3=data6
  _xmm6 = _mm_add_epi16 (_xmm6, _xmm1);   //; _xmm6=data0
  _xmm2 = _mm_add_epi16 (_xmm2, _xmm5);   //; _xmm2=data2

  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 4 * 8), _xmm4);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 6 * 8), _xmm3);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 0 * 8), _xmm6);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 2 * 8), _xmm2);

  //; -- Odd part

  _xmm1 = _wk0;   //; _xmm1=tmp6
  _xmm5 = _wk1;   //; _xmm5=tmp7

  _xmm7 = _mm_add_epi16 (_xmm7, _xmm0);   //; _xmm7=tmp10
  _xmm0 = _mm_add_epi16 (_xmm0, _xmm1);   //; _xmm0=tmp11
  _xmm1 = _mm_add_epi16 (_xmm1, _xmm5);   //; _xmm1=tmp12, _xmm5=tmp7

  _xmm7 = _mm_slli_epi16 (_xmm7, PRE_MULTIPLY_SCALE_BITS);
  _xmm1 = _mm_slli_epi16 (_xmm1, PRE_MULTIPLY_SCALE_BITS);

  _xmm0 = _mm_slli_epi16 (_xmm0, PRE_MULTIPLY_SCALE_BITS);
  _xmm0 = _mm_mulhi_epi16 (_xmm0, _PW_F0707);   //; _xmm0=z3

  _xmm4 = _xmm7;   //; _xmm4=tmp10
  _xmm7 = _mm_sub_epi16 (_xmm7, _xmm1);
  _xmm7 = _mm_mulhi_epi16 (_xmm7, _PW_F0382);   //; _xmm7=z5
  _xmm4 = _mm_mulhi_epi16 (_xmm4, _PW_F0541);   //; _xmm4=MULTIPLY( tmp10,FIX_0_541196)
  _xmm1 = _mm_mulhi_epi16 (_xmm1, _PW_F1306);   //; _xmm1=MULTIPLY( tmp12,FIX_1_306562 )

  _xmm4 = _mm_add_epi16 (_xmm4, _xmm7);   //; _xmm4=z2
  _xmm1 = _mm_add_epi16 (_xmm1, _xmm7);   //; _xmm1=z4


  _xmm3 = _xmm5;
  _xmm5 = _mm_sub_epi16 (_xmm5, _xmm0);   //; _xmm5=z13
  _xmm3 = _mm_add_epi16 (_xmm3, _xmm0);   //; _xmm3=z11

  _xmm6 = _xmm5;
  _xmm2 = _xmm3;
  _xmm5 = _mm_sub_epi16 (_xmm5, _xmm4);   //; _xmm5=data3
  _xmm3 = _mm_sub_epi16 (_xmm3, _xmm1);   //; _xmm3=data7
  _xmm6 = _mm_add_epi16 (_xmm6, _xmm4);   //; _xmm6=data5
  _xmm2 = _mm_add_epi16 (_xmm2, _xmm1);   //; _xmm2=data1

  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 3 * 8), _xmm5);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 7 * 8), _xmm3);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 5 * 8), _xmm6);
  _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (buf + 1 * 8), _xmm2);
}

}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward

#endif
