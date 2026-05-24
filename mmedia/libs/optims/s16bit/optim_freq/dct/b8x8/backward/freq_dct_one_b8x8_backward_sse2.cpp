/**
\file
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_backward.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
#  if 0
;
; jidctfst.asm - fast integer IDCT (SSE2 )
;
; Copyright 2009 Pierre Ossman <ossman@cendio.se> for Cendio AB
;
; Based on the x86 SIMD extension for IJG JPEG library
; Copyright (C) 1999-2006, MIYASAKA Masaru.
; For conditions of distribution and use, see copyright notice in jsimdext.inc
;
; This file should be assembled with NASM (Netwide Assembler),
; can not be assembled with Microsofts MASM or any compatible
; assembler (including Borlands Turbo Assembler).
; NASM is available from http://nasm.sourceforge.net/ or
; http://sourceforge.net/project/showfiles.php?group_id=6208
;
; This file contains a fast, not so accurate integer implementation of
; the inverse DCT (Discrete Cosine Transform). The following code is
; based directly on the IJGs original jidctfst.c; see the jidctfst.c
; for more details.
;
; [TAB8]
#  endif

#  define CONST_BITS 8   //; 14 is also OK.
#  define PASS1_BITS 2

#  if 0


%if IFAST_SCALE_BITS != PASS1_BITS
%error "'IFAST_SCALE_BITS' must be equal to 'PASS1_BITS'."
%endif

%if CONST_BITS == 8
F_1_082 equ     277             ; FIX(1.082392200)
F_1_414 equ     362             ; FIX(1.414213562 )
F_1_847 equ     473             ; FIX(1.847759065 )
F_2_613 equ     669             ; FIX(2.613125930)
F_1_613 equ     (F_2_613 - 256) ; FIX(2.613125930) - FIX(1 )
%else
; NASM cannot do compile-time arithmetic on floating-point constants.
%define DESCALE( x,n)  ( ( ( x )+(1<<( (n)-1 ) ) )>>(n) )
F_1_082 equ     DESCALE(1162209775,30-CONST_BITS)       ; FIX(1.082392200)
F_1_414 equ     DESCALE(1518500249,30-CONST_BITS)       ; FIX(1.414213562 )
F_1_847 equ     DESCALE(1984016188,30-CONST_BITS)       ; FIX(1.847759065 )
F_2_613 equ     DESCALE(2805822602,30-CONST_BITS)       ; FIX(2.613125930)
F_1_613 equ     (F_2_613 - (1 << CONST_BITS) )   ; FIX(2.613125930) - FIX(1 )
%endif
#  endif

#  define PRE_MULTIPLY_SCALE_BITS 2
#  define CONST_SHIFT (16 - PRE_MULTIPLY_SCALE_BITS - CONST_BITS)

#  if 0
; --------------------------------------------------------------------------
        SECTION SEG_CONST

; PRE_MULTIPLY_SCALE_BITS <= 2 ( to avoid overflow)
; CONST_BITS + CONST_SHIFT + PRE_MULTIPLY_SCALE_BITS == 16 (for _mm_mulhi_epi16()

%define PRE_MULTIPLY_SCALE_BITS   2
%define CONST_SHIFT     (16 - PRE_MULTIPLY_SCALE_BITS - CONST_BITS)

        alignz  16
        global  EXTN(jconst_idct_ifast_sse2 )

EXTN(jconst_idct_ifast_sse2 ):

PW_F1414        times 8 dw  F_1_414 << CONST_SHIFT
PW_F1847        times 8 dw  F_1_847 << CONST_SHIFT
PW_MF1613       times 8 dw -F_1_613 << CONST_SHIFT
PW_F1082        times 8 dw  F_1_082 << CONST_SHIFT
PB_CENTERJSAMP  times 16 db CENTERJSAMPLE

        alignz  16

; --------------------------------------------------------------------------
        SECTION SEG_TEXT
        BITS    32
;
; Perform dequantization and inverse DCT on one block of coefficients.
;
; GLOBAL()
; jsimd_idct_ifast_sse2 (void *dct_table, JCOEFPTR coef_block,
;                       JSAMPARRAY output_buf, JDIMENSION output_col)
;

%define dct_table(b )    (b )+8           ; jpeg_component_info *compptr
%define coef_block(b )   (b )+12          ; JCOEFPTR coef_block
%define output_buf(b )   (b )+16          ; JSAMPARRAY output_buf
%define output_col(b )   (b )+20          ; JDIMENSION output_col

%define original_ebp    ebp+0
%define wk(i)           ebp-(WK_NUM-(i) ) *SIZEOF_XMMWORD ; xmmword wk[WK_NUM]
%define WK_NUM          2


#  endif

void
sse2_b8x8 (std::int16_t* buf)
{
#  if 1
  return;
#  else
  __m128i xmm0;
  __m128i xmm1;
  __m128i xmm2;
  __m128i xmm3;
  __m128i xmm4;
  __m128i xmm5;
  __m128i xmm6;
  __m128i xmm7;
  __m128i wk0;
  __m128i wk1;
  // const __m128i   _PW_F0382 = _mm_set1_epi16( 98 );
  // const __m128i   _PW_F0541 = _mm_set1_epi16( 139 );
  // const __m128i   _PW_F0707 = _mm_set1_epi16( 181 );
  // const __m128i   _PW_F1306 = _mm_set1_epi16( 334 );

  U3_ASSERT_SIGNAL ("failed");
#    if 0
;       mov     eax, [original_ebp]
        mov     edx, POINTER [dct_table(eax )]           ; quantptr
        mov     esi, JCOEFPTR [coef_block(eax )]         ; inptr

%ifndef NO_ZERO_COLUMN_TEST_IFAST_SSE2
        mov     eax, DWORD [DWBLOCK(1,0,esi,SIZEOF_JCOEF)]
        or      eax, DWORD [DWBLOCK(2,0,esi,SIZEOF_JCOEF)]
        jnz     near .columnDCT

        movdqa  xmm0, XMMWORD [XMMBLOCK(1,0,esi,SIZEOF_JCOEF)]
        movdqa  xmm1, XMMWORD [XMMBLOCK(2,0,esi,SIZEOF_JCOEF)]
        por     xmm0, XMMWORD [XMMBLOCK( 3,0,esi,SIZEOF_JCOEF)]
        por     xmm1, XMMWORD [XMMBLOCK(4,0,esi,SIZEOF_JCOEF)]
        por     xmm0, XMMWORD [XMMBLOCK(5,0,esi,SIZEOF_JCOEF)]
        por     xmm1, XMMWORD [XMMBLOCK( 6,0,esi,SIZEOF_JCOEF)]
        por     xmm0, XMMWORD [XMMBLOCK(7,0,esi,SIZEOF_JCOEF)]
        por     xmm1,xmm0
        _mm_packs_epi16( xmm1,xmm1
        _mm_packs_epi16( xmm1,xmm1
        movd    eax,xmm1
        test    eax,eax
        jnz     std::int16_t .columnDCT

        ; -- AC terms all zero

        movdqa  xmm0, XMMWORD [XMMBLOCK(0,0,esi,SIZEOF_JCOEF)]
        _mm_mullo_epi16(  xmm0, XMMWORD [XMMBLOCK(0,0,edx,SIZEOF_ISLOW_MULT_TYPE)]

        movdqa    xmm7,xmm0             ; xmm0=in0=(00 01 02 03 04 05 06 07)
        _mm_unpacklo_epi16( xmm0,xmm0             ; xmm0=(00 00 01 01 02 02 03 03)
        _mm_unpackhi_epi16( xmm7,xmm7             ; xmm7=(04 04 05 05 06 06 07 07)

        _mm_shuffle_epi32(  xmm6,xmm0,0x00          ; xmm6=col0=(00 00 00 00 00 00 00 00)
        _mm_shuffle_epi32(  xmm2,xmm0,0x55          ; xmm2=col1=(01 01 01 01 01 01 01 01 )
        _mm_shuffle_epi32(  xmm5,xmm0,0xAA          ; xmm5=col2=(02 02 02 02 02 02 02 02 )
        _mm_shuffle_epi32(  xmm0,xmm0,0xFF          ; xmm0=col3=(03 03 03 03 03 03 03 03)
        _mm_shuffle_epi32(  xmm1,xmm7,0x00          ; xmm1=col4=(04 04 04 04 04 04 04 04 )
        _mm_shuffle_epi32(  xmm4,xmm7,0x55          ; xmm4=col5=(05 05 05 05 05 05 05 05 )
        _mm_shuffle_epi32(  xmm3,xmm7,0xAA          ; xmm3=col6=(06 06 06 06 06 06 06 06)
        _mm_shuffle_epi32(  xmm7,xmm7,0xFF          ; xmm7=col7=(07 07 07 07 07 07 07 07)

        movdqa  wk0, xmm2   ; wk(0)=col1
        movdqa  wk1, xmm0   ; wk(1 )=col3
        jmp     near .column_end
        alignx  16,7
%endif
#    endif

  U3_ASSERT_SIGNAL ("failed");
#    if 0
.columnDCT:

        ; -- Even part

        movdqa  xmm0, XMMWORD [XMMBLOCK(0,0,esi,SIZEOF_JCOEF)]
        movdqa  xmm1, XMMWORD [XMMBLOCK(2,0,esi,SIZEOF_JCOEF)]
        _mm_mullo_epi16(  xmm0, XMMWORD [XMMBLOCK(0,0,edx,SIZEOF_IFAST_MULT_TYPE)]
        _mm_mullo_epi16(  xmm1, XMMWORD [XMMBLOCK(2,0,edx,SIZEOF_IFAST_MULT_TYPE)]
        movdqa  xmm2, XMMWORD [XMMBLOCK(4,0,esi,SIZEOF_JCOEF)]
        movdqa  xmm3, XMMWORD [XMMBLOCK( 6,0,esi,SIZEOF_JCOEF)]
        _mm_mullo_epi16(  xmm2, XMMWORD [XMMBLOCK(4,0,edx,SIZEOF_IFAST_MULT_TYPE)]
        _mm_mullo_epi16(  xmm3, XMMWORD [XMMBLOCK( 6,0,edx,SIZEOF_IFAST_MULT_TYPE)]
#    endif


  xmm4 = xmm0;
  xmm5 = xmm1;
  xmm0 = _mm_sub_epi16 (xmm0, xmm2);   //; xmm0=tmp11
  xmm1 = _mm_sub_epi16 (xmm1, xmm3);   //
  xmm4 = _mm_add_epi16 (xmm4, xmm2);   //; xmm4=tmp10
  xmm5 = _mm_add_epi16 (xmm5, xmm3);   //; xmm5=tmp13

  xmm1 = _mm_slli_epi16 (xmm1, PRE_MULTIPLY_SCALE_BITS);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        _mm_mulhi_epi16(  xmm1,[GOTOFF(ebx,PW_F1414 )] );//
#    endif
  xmm1 = _mm_sub_epi16 (xmm1, xmm5);   //; xmm1=tmp12

  xmm6 = xmm4;                         //
  xmm7 = xmm0;                         //
  xmm4 = _mm_sub_epi16 (xmm4, xmm5);   //; xmm4=tmp3
  xmm0 = _mm_sub_epi16 (xmm0, xmm1);   //; xmm0=tmp2
  xmm6 = _mm_add_epi16 (xmm6, xmm5);   //; xmm6=tmp0
  xmm7 = _mm_add_epi16 (xmm7, xmm1);   //; xmm7=tmp1

  wk1 = xmm4;   //; wk(1 )=tmp3
  wk0 = xmm0;   //; wk(0)=tmp2

  //; -- Odd part

  U3_ASSERT_SIGNAL ("failed");
#    if 0
        movdqa  xmm2, XMMWORD [XMMBLOCK(1,0,esi,SIZEOF_JCOEF)]
        movdqa  xmm3, XMMWORD [XMMBLOCK( 3,0,esi,SIZEOF_JCOEF)]
        _mm_mullo_epi16(  xmm2, XMMWORD [XMMBLOCK(1,0,edx,SIZEOF_IFAST_MULT_TYPE)] );  //
        _mm_mullo_epi16(  xmm3, XMMWORD [XMMBLOCK( 3,0,edx,SIZEOF_IFAST_MULT_TYPE)] ); //
        movdqa  xmm5, XMMWORD [XMMBLOCK(5,0,esi,SIZEOF_JCOEF)] );            //
        movdqa  xmm1, XMMWORD [XMMBLOCK(7,0,esi,SIZEOF_JCOEF)] );            //
        _mm_mullo_epi16(  xmm5, XMMWORD [XMMBLOCK(5,0,edx,SIZEOF_IFAST_MULT_TYPE)] );  //
        _mm_mullo_epi16(  xmm1, XMMWORD [XMMBLOCK(7,0,edx,SIZEOF_IFAST_MULT_TYPE)] );  //
#    endif

  xmm4 = xmm2;
  xmm0 = xmm5;
  xmm2 = _mm_sub_epi16 (xmm2, xmm1);   //; xmm2=z12
  xmm5 = _mm_sub_epi16 (xmm5, xmm3);   //; xmm5=z10
  xmm4 = _mm_add_epi16 (xmm4, xmm1);   //; xmm4=z11
  xmm0 = _mm_add_epi16 (xmm0, xmm3);   //; xmm0=z13

  xmm1 = xmm5;                                             //; xmm1=z10(unscaled)
  xmm2 = _mm_slli_epi16 (xmm2, PRE_MULTIPLY_SCALE_BITS);   //
  xmm5 = _mm_slli_epi16 (xmm5, PRE_MULTIPLY_SCALE_BITS);   //

  xmm3 = xmm4;
  xmm4 = _mm_sub_epi16 (xmm4, xmm0);   //
  xmm3 = _mm_add_epi16 (xmm3, xmm0);   //; xmm3=tmp7

  xmm4 = _mm_slli_epi16 (xmm4, PRE_MULTIPLY_SCALE_BITS);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        _mm_mulhi_epi16(  xmm4,[GOTOFF(ebx,PW_F1414 )] );                //xmm4=tmp11
#    endif
  //; To avoid overflow...
  //;
  //; (Original)
  //; tmp12 = -2.613125930 * z10 + z5;
  //;
  //; (This implementation)
  //; tmp12 = (-1.613125930 - 1 ) * z10 + z5;
  //;       = -1.613125930 * z10 - z10 + z5;

  xmm0 = xmm5;
  xmm5 = _mm_add_epi16 (xmm5, xmm2);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        _mm_mulhi_epi16(  xmm5,[GOTOFF(ebx,PW_F1847)] );               //; xmm5=z5
        _mm_mulhi_epi16(  xmm0,[GOTOFF(ebx,PW_MF1613)] );                //
        _mm_mulhi_epi16(  xmm2,[GOTOFF(ebx,PW_F1082 )] );                //
#    endif
  xmm0 = _mm_sub_epi16 (xmm0, xmm1);   //
  xmm2 = _mm_sub_epi16 (xmm2, xmm5);   //; xmm2=tmp10
  xmm0 = _mm_add_epi16 (xmm0, xmm5);   //; xmm0=tmp12

  //; -- Final output stage

  xmm0 = _mm_sub_epi16 (xmm0, xmm3);   //; xmm0=tmp6
  xmm1 = xmm6;                         //
  xmm5 = xmm7;                         //
  xmm6 = _mm_add_epi16 (xmm6, xmm3);   //; xmm6=data0=(00 01 02 03 04 05 06 07)
  xmm7 = _mm_add_epi16 (xmm7, xmm0);   //; xmm7=data1=(10 11 12 13 14 15 16 17)
  xmm1 = _mm_sub_epi16 (xmm1, xmm3);   //; xmm1=data7=(70 71 72 73 74 75 76 77)
  xmm5 = _mm_sub_epi16 (xmm5, xmm0);   //; xmm5=data6=( 60 61 62 63 64 65 66 67)
  xmm4 = _mm_sub_epi16 (xmm4, xmm0);   //; xmm4=tmp5

  xmm3 = xmm6;                              //; transpose coefficients(phase 1 )
  xmm6 = _mm_unpacklo_epi16 (xmm6, xmm7);   //; xmm6=(00 10 01 11 02 12 03 13)
  xmm3 = _mm_unpackhi_epi16 (xmm3, xmm7);   //; xmm3=(04 14 05 15 06 16 07 17)
  xmm0 = xmm5;                              //; transpose coefficients(phase 1 )
  xmm5 = _mm_unpacklo_epi16 (xmm5, xmm1);   //; xmm5=( 60 70 61 71 62 72 63 73)
  xmm0 = _mm_unpackhi_epi16 (xmm0, xmm1);   //; xmm0=( 64 74 65 75 66 76 67 77)

  xmm7 = wk0;   //; xmm7=tmp2
  xmm1 = wk1;   //; xmm1=tmp3

  wk0 = xmm5;   //; wk(0)=( 60 70 61 71 62 72 63 73)
  wk1 = xmm0;   //; wk(1 )=( 64 74 65 75 66 76 67 77)

  xmm2 = _mm_add_epi16 (xmm2, xmm4);   //; xmm2=tmp4
  xmm5 = xmm7;                         //
  xmm0 = xmm1;                         //
  xmm7 = _mm_add_epi16 (xmm7, xmm4);   //; xmm7=data2=(20 21 22 23 24 25 26 27)
  xmm1 = _mm_add_epi16 (xmm1, xmm2);   //; xmm1=data4=(40 41 42 43 44 45 46 47)
  xmm5 = _mm_sub_epi16 (xmm5, xmm4);   //; xmm5=data5=(50 51 52 53 54 55 56 57)
  xmm0 = _mm_sub_epi16 (xmm0, xmm2);   //; xmm0=data3=( 30 31 32 33 34 35 36 37)

  xmm4 = xmm7;                              //; transpose coefficients(phase 1 )
  xmm7 = _mm_unpacklo_epi16 (xmm7, xmm0);   //; xmm7=(20 30 21 31 22 32 23 33)
  xmm4 = _mm_unpackhi_epi16 (xmm4, xmm0);   //; xmm4=(24 34 25 35 26 36 27 37)
  xmm2 = xmm1;                              //; transpose coefficients(phase 1 )
  xmm1 = _mm_unpacklo_epi16 (xmm1, xmm5);   //; xmm1=(40 50 41 51 42 52 43 53)
  xmm2 = _mm_unpackhi_epi16 (xmm2, xmm5);   //; xmm2=(44 54 45 55 46 56 47 57)

  xmm0 = xmm3;                              //; transpose coefficients(phase 2 )
  xmm3 = _mm_unpacklo_epi32 (xmm3, xmm4);   //; xmm3=(04 14 24 34 05 15 25 35 )
  xmm0 = _mm_unpackhi_epi32 (xmm0, xmm4);   //; xmm0=(06 16 26 36 07 17 27 37)
  xmm5 = xmm6;                              //; transpose coefficients(phase 2 )
  xmm6 = _mm_unpacklo_epi32 (xmm6, xmm7);   //; xmm6=(00 10 20 30 01 11 21 31 )
  xmm5 = _mm_unpackhi_epi32 (xmm5, xmm7);   //; xmm5=(02 12 22 32 03 13 23 33)

  xmm4 = wk0;   //; xmm4=( 60 70 61 71 62 72 63 73)
  xmm7 = wk1;   //; xmm7=( 64 74 65 75 66 76 67 77)

  wk0 = xmm3;   //; wk(0)=(04 14 24 34 05 15 25 35 )
  wk1 = xmm0;   //; wk(1 )=(06 16 26 36 07 17 27 37)

  xmm3 = xmm1;                              //; transpose coefficients(phase 2 )
  xmm1 = _mm_unpacklo_epi32 (xmm1, xmm4);   //; xmm1=(40 50 60 70 41 51 61 71 )
  xmm3 = _mm_unpackhi_epi32 (xmm3, xmm4);   //; xmm3=(42 52 62 72 43 53 63 73)
  xmm0 = xmm2;                              //; transpose coefficients(phase 2 )
  xmm2 = _mm_unpacklo_epi32 (xmm2, xmm7);   //; xmm2=(44 54 64 74 45 55 65 75 )
  xmm0 = _mm_unpackhi_epi32 (xmm0, xmm7);   //; xmm0=(46 56 66 76 47 57 67 77)

  xmm4 = xmm6;                              //; transpose coefficients(phase 3)
  xmm6 = _mm_unpacklo_epi64 (xmm6, xmm1);   //; xmm6=col0=(00 10 20 30 40 50 60 70)
  xmm4 = _mm_unpackhi_epi64 (xmm4, xmm1);   //; xmm4=col1=(01 11 21 31 41 51 61 71 )
  xmm7 = xmm5;                              //; transpose coefficients(phase 3)
  xmm5 = _mm_unpacklo_epi64 (xmm5, xmm3);   //; xmm5=col2=(02 12 22 32 42 52 62 72 )
  xmm7 = _mm_unpackhi_epi64 (xmm7, xmm3);   //; xmm7=col3=(03 13 23 33 43 53 63 73)

  xmm1 = wk0;   //; xmm1=(04 14 24 34 05 15 25 35 )
  xmm3 = wk1;   //; xmm3=(06 16 26 36 07 17 27 37)

  wk0 = xmm4;   //; wk(0)=col1
  wk1 = xmm7;   //; wk(1 )=col3

  xmm4 = xmm1;                              //; transpose coefficients(phase 3)
  xmm1 = _mm_unpacklo_epi64 (xmm1, xmm2);   //; xmm1=col4=(04 14 24 34 44 54 64 74 )
  xmm4 = _mm_unpackhi_epi64 (xmm4, xmm2);   //; xmm4=col5=(05 15 25 35 45 55 65 75 )
  xmm7 = xmm3;                              //; transpose coefficients(phase 3)
  xmm3 = _mm_unpacklo_epi64 (xmm3, xmm0);   //; xmm3=col6=(06 16 26 36 46 56 66 76)
  xmm7 = _mm_unpackhi_epi64 (xmm7, xmm0);   //; xmm7=col7=(07 17 27 37 47 57 67 77)

  //.column_end:

  //; -- Prefetch the next coefficient block

  U3_ASSERT_SIGNAL ("failed");
#    if 0
        prefetchnta [esi + DCTSIZE2*SIZEOF_JCOEF + 0* 32]
        prefetchnta [esi + DCTSIZE2*SIZEOF_JCOEF + 1* 32]
        prefetchnta [esi + DCTSIZE2*SIZEOF_JCOEF + 2* 32]
        prefetchnta [esi + DCTSIZE2*SIZEOF_JCOEF + 3* 32]
#    endif
  //; ---- Pass 2: process rows from work array, store into output array.

  U3_ASSERT_SIGNAL ("failed");
#    if 0
        mov     eax, [original_ebp]
        mov     edi, JSAMPARRAY [output_buf(eax )]       ; (JSAMPROW *)
        mov     eax, JDIMENSION [output_col(eax )]
#    endif
  //; -- Even part

  //; xmm6=col0, xmm5=col2, xmm1=col4, xmm3=col6

  xmm2 = xmm6;                         //
  xmm0 = xmm5;                         //
  xmm6 = _mm_sub_epi16 (xmm6, xmm1);   //; xmm6=tmp11
  xmm5 = _mm_sub_epi16 (xmm5, xmm3);   //
  xmm2 = _mm_add_epi16 (xmm2, xmm1);   //; xmm2=tmp10
  xmm0 = _mm_add_epi16 (xmm0, xmm3);   //; xmm0=tmp13

  xmm5 = _mm_slli_epi16 (xmm5, PRE_MULTIPLY_SCALE_BITS);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        xmm5 = _mm_mulhi_epi16(  xmm5,[GOTOFF(ebx,PW_F1414 )] );            //
#    endif
  xmm5 = _mm_sub_epi16 (xmm5, xmm0);   //; xmm5=tmp12

  xmm1 = xmm2;                         //
  xmm3 = xmm6;                         //
  xmm2 = _mm_sub_epi16 (xmm2, xmm0);   //; xmm2=tmp3
  xmm6 = _mm_sub_epi16 (xmm6, xmm5);   //; xmm6=tmp2
  xmm1 = _mm_add_epi16 (xmm1, xmm0);   //; xmm1=tmp0
  xmm3 = _mm_add_epi16 (xmm3, xmm5);   //; xmm3=tmp1

  xmm0 = wk0;   //; xmm0=col1
  xmm5 = wk1;   //; xmm5=col3

  wk0 = xmm2;   //; wk(0)=tmp3
  wk1 = xmm6;   //; wk(1 )=tmp2

  //; -- Odd part

  //; xmm0=col1, xmm5=col3, xmm4=col5, xmm7=col7

  xmm2 = xmm0;                         //
  xmm6 = xmm4;                         //
  xmm0 = _mm_sub_epi16 (xmm0, xmm7);   //; xmm0=z12
  xmm4 = _mm_sub_epi16 (xmm4, xmm5);   //; xmm4=z10
  xmm2 = _mm_add_epi16 (xmm2, xmm7);   //; xmm2=z11
  xmm6 = _mm_add_epi16 (xmm6, xmm5);   //; xmm6=z13

  xmm7 = xmm4;                                             //; xmm7=z10(unscaled)
  xmm0 = _mm_slli_epi16 (xmm0, PRE_MULTIPLY_SCALE_BITS);   //
  xmm4 = _mm_slli_epi16 (xmm4, PRE_MULTIPLY_SCALE_BITS);   //

  xmm5 = xmm2;                         //
  xmm2 = _mm_sub_epi16 (xmm2, xmm6);   //
  xmm5 = _mm_add_epi16 (xmm5, xmm6);   //; xmm5=tmp7

  xmm2 = _mm_slli_epi16 (xmm2, PRE_MULTIPLY_SCALE_BITS);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        _mm_mulhi_epi16(  xmm2,[GOTOFF(ebx,PW_F1414 )] );                //; xmm2=tmp11
#    endif
  //; To avoid overflow...
  //;
  //; (Original)
  //; tmp12 = -2.613125930 * z10 + z5;
  //;
  //; (This implementation)
  //; tmp12 = (-1.613125930 - 1 ) * z10 + z5;
  //;       = -1.613125930 * z10 - z10 + z5;

  xmm6 = xmm4;
  xmm4 = _mm_add_epi16 (xmm4, xmm0);   //
  U3_ASSERT_SIGNAL ("failed");
#    if 0
        _mm_mulhi_epi16(  xmm4,[GOTOFF(ebx,PW_F1847)] );               //; xmm4=z5
        _mm_mulhi_epi16(  xmm6,[GOTOFF(ebx,PW_MF1613)] );                //
        _mm_mulhi_epi16(  xmm0,[GOTOFF(ebx,PW_F1082 )] );                //
#    endif
  xmm6 = _mm_sub_epi16 (xmm6, xmm7);   //
  xmm0 = _mm_sub_epi16 (xmm0, xmm4);   //; xmm0=tmp10
  xmm6 = _mm_add_epi16 (xmm6, xmm4);   //; xmm6=tmp12

  //; -- Final output stage

  xmm6 = _mm_sub_epi16 (xmm6, xmm5);                //; xmm6=tmp6
  xmm7 = xmm1;                                      //
  xmm4 = xmm3;                                      //
  xmm1 = _mm_add_epi16 (xmm1, xmm5);                //; xmm1=data0=(00 10 20 30 40 50 60 70)
  xmm3 = _mm_add_epi16 (xmm3, xmm6);                //; xmm3=data1=(01 11 21 31 41 51 61 71 )
  xmm1 = _mm_srai_epi16 (xmm1, (PASS1_BITS + 3));   //; descale
  xmm3 = _mm_srai_epi16 (xmm3, (PASS1_BITS + 3));   //; descale
  xmm7 = _mm_sub_epi16 (xmm7, xmm5);                //; xmm7=data7=(07 17 27 37 47 57 67 77)
  xmm4 = _mm_sub_epi16 (xmm4, xmm6);                //; xmm4=data6=(06 16 26 36 46 56 66 76)
  xmm7 = _mm_srai_epi16 (xmm7, (PASS1_BITS + 3));   //; descale
  xmm4 = _mm_srai_epi16 (xmm4, (PASS1_BITS + 3));   //; descale
  xmm2 = _mm_sub_epi16 (xmm2, xmm6);                //; xmm2=tmp5

  xmm1 = _mm_packs_epi16 (xmm1, xmm4);   //; xmm1=(00 10 20 30 40 50 60 70 06 16 26 36 46 56 66 76)
  xmm3 = _mm_packs_epi16 (xmm3, xmm7);   //; xmm3=(01 11 21 31 41 51 61 71 07 17 27 37 47 57 67 77)

  xmm5 = wk1;   //; xmm5=tmp2
  xmm6 = wk0;   //; xmm6=tmp3

  xmm0 = _mm_add_epi16 (xmm0, xmm2);                //; xmm0=tmp4
  xmm4 = xmm5;                                      //
  xmm7 = xmm6;                                      //
  xmm5 = _mm_add_epi16 (xmm5, xmm2);                //; xmm5=data2=(02 12 22 32 42 52 62 72 )
  xmm6 = _mm_add_epi16 (xmm6, xmm0);                //; xmm6=data4=(04 14 24 34 44 54 64 74 )
  xmm5 = _mm_srai_epi16 (xmm5, (PASS1_BITS + 3));   //; descale
  xmm6 = _mm_srai_epi16 (xmm6, (PASS1_BITS + 3));   //; descale
  xmm4 = _mm_sub_epi16 (xmm4, xmm2);                //; xmm4=data5=(05 15 25 35 45 55 65 75 )
  xmm7 = _mm_sub_epi16 (xmm7, xmm0);                //; xmm7=data3=(03 13 23 33 43 53 63 73)
  xmm4 = _mm_srai_epi16 (xmm4, (PASS1_BITS + 3));   //; descale
  xmm7 = _mm_srai_epi16 (xmm7, (PASS1_BITS + 3));   //; descale

  U3_ASSERT_SIGNAL ("failed");
#    if 0
        movdqa    xmm2,[GOTOFF(ebx,PB_CENTERJSAMP)] );//; xmm2=[PB_CENTERJSAMP]
#    endif

  xmm5 = _mm_packs_epi16 (xmm5, xmm6);   //; xmm5=(02 12 22 32 42 52 62 72 04 14 24 34 44 54 64 74 )
  xmm7 = _mm_packs_epi16 (xmm7, xmm4);   //; xmm7=(03 13 23 33 43 53 63 73 05 15 25 35 45 55 65 75 )

  xmm1 = _mm_add_epi8 (xmm1, xmm2);   //
  xmm3 = _mm_add_epi8 (xmm3, xmm2);   //
  xmm5 = _mm_add_epi8 (xmm5, xmm2);   //
  xmm7 = _mm_add_epi8 (xmm7, xmm2);   //

  xmm0 = xmm1;                             //; transpose coefficients(phase 1 )
  xmm1 = _mm_unpacklo_epi8 (xmm1, xmm3);   //; xmm1=(00 01 10 11 20 21 30 31 40 41 50 51 60 61 70 71 )
  xmm0 = _mm_unpackhi_epi8 (xmm0, xmm3);   //; xmm0=(06 07 16 17 26 27 36 37 46 47 56 57 66 67 76 77)
  xmm6 = xmm5;                             //; transpose coefficients(phase 1 )
  xmm5 = _mm_unpacklo_epi8 (xmm5, xmm7);   //; xmm5=(02 03 12 13 22 23 32 33 42 43 52 53 62 63 72 73)
  xmm6 = _mm_unpackhi_epi8 (xmm6, xmm7);   //; xmm6=(04 05 14 15 24 25 34 35 44 45 54 55 64 65 74 75 )

  xmm4 = xmm1;                              //; transpose coefficients(phase 2 )
  xmm1 = _mm_unpacklo_epi16 (xmm1, xmm5);   //; xmm1=(00 01 02 03 10 11 12 13 20 21 22 23 30 31 32 33)
  xmm4 = _mm_unpackhi_epi16 (xmm4, xmm5);   //; xmm4=(40 41 42 43 50 51 52 53 60 61 62 63 70 71 72 73)
  xmm2 = xmm6;                              //; transpose coefficients(phase 2 )
  xmm6 = _mm_unpacklo_epi16 (xmm6, xmm0);   //; xmm6=(04 05 06 07 14 15 16 17 24 25 26 27 34 35 36 37)
  xmm2 = _mm_unpackhi_epi16 (xmm2, xmm0);   //; xmm2=(44 45 46 47 54 55 56 57 64 65 66 67 74 75 76 77)

  xmm3 = xmm1;                              //; transpose coefficients(phase 3)
  xmm1 = _mm_unpacklo_epi32 (xmm1, xmm6);   //; xmm1=(00 01 02 03 04 05 06 07 10 11 12 13 14 15 16 17)
  xmm3 = _mm_unpackhi_epi32 (xmm3, xmm6);   //; xmm3=(20 21 22 23 24 25 26 27 30 31 32 33 34 35 36 37)
  xmm7 = xmm4;                              //; transpose coefficients(phase 3)
  xmm4 = _mm_unpacklo_epi32 (xmm4, xmm2);   //; xmm4=(40 41 42 43 44 45 46 47 50 51 52 53 54 55 56 57)
  xmm7 = _mm_unpackhi_epi32 (xmm7, xmm2);   //; xmm7=( 60 61 62 63 64 65 66 67 70 71 72 73 74 75 76 77)

  xmm5 = _mm_shuffle_epi32 (xmm1, 0x4E);   //  ; xmm5=(10 11 12 13 14 15 16 17 00 01 02 03 04 05 06 07)
  xmm0 = _mm_shuffle_epi32 (xmm3, 0x4E);   //  ; xmm0=( 30 31 32 33 34 35 36 37 20 21 22 23 24 25 26 27)
  xmm6 = _mm_shuffle_epi32 (xmm4, 0x4E);   //  ; xmm6=(50 51 52 53 54 55 56 57 40 41 42 43 44 45 46 47)
  xmm2 = _mm_shuffle_epi32 (xmm7, 0x4E);   //  ; xmm2=(70 71 72 73 74 75 76 77 60 61 62 63 64 65 66 67)

  U3_ASSERT_SIGNAL ("failed");
#    if 0
        mov     edx, JSAMPROW [edi+0*SIZEOF_JSAMPROW] );//
        mov     esi, JSAMPROW [edi+2*SIZEOF_JSAMPROW] );//
        movq    XMM_MMWORD [edx+eax*SIZEOF_JSAMPLE], xmm1 );//
        movq    XMM_MMWORD [esi+eax*SIZEOF_JSAMPLE], xmm3 );//
        mov     edx, JSAMPROW [edi+4*SIZEOF_JSAMPROW] );//
        mov     esi, JSAMPROW [edi+6*SIZEOF_JSAMPROW] );//
        movq    XMM_MMWORD [edx+eax*SIZEOF_JSAMPLE], xmm4 );//
        movq    XMM_MMWORD [esi+eax*SIZEOF_JSAMPLE], xmm7 );//

        mov     edx, JSAMPROW [edi+1*SIZEOF_JSAMPROW] );//
        mov     esi, JSAMPROW [edi+3*SIZEOF_JSAMPROW] );//
        movq    XMM_MMWORD [edx+eax*SIZEOF_JSAMPLE], xmm5 );//
        movq    XMM_MMWORD [esi+eax*SIZEOF_JSAMPLE], xmm0 );//
        mov     edx, JSAMPROW [edi+5*SIZEOF_JSAMPROW] );//
        mov     esi, JSAMPROW [edi+7*SIZEOF_JSAMPROW] );//
        movq    XMM_MMWORD [edx+eax*SIZEOF_JSAMPLE], xmm6 );//
        movq    XMM_MMWORD [esi+eax*SIZEOF_JSAMPLE], xmm2 );//
#    endif
#  endif
}

}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward

#endif
