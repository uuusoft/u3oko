
;/******************************************************************************
; *                                                                            *
; *  fdct_mmx.asm, MMX optimized forward DCT                                   *
; *                                                                            *
; *  Initial, but incomplete version provided by Intel at AppNote AP-922       *
; *  http://developer.intel.com/vtune/cbts/strmsimd/922down.htm                *
; *  Copyright (C) 1999 Intel Corporation,                                     *
; *                                                                            *
; *  completed and corrected in fdctmm32.c/fdctmm32.doc,                       *
; *  http://members.tripod.com/~liaor                                          *
; *  Copyright (C) 2000 - Royce Shih-Wea Liao <liaor@iname.com>,               *
; *                                                                            *
; *                                                                            *																			   *
; *  Detect zero block prior DCT and quantizaton							   *
; *  FDCT_one_ROW macro, Sigma Designs Inc.
; *
; *  ported to NASM and some minor changes                                     * 
; *  Copyright (C) 2001 - Michael Militzer <isibaar@xvid.org>														   *
; *                                                                            *
; ******************************************************************************/
;

BITS 32

%define INP				eax
%define TABLE			ebx
%define TABLEF			ebx
%define OUT				ecx
%define round_frw_row	edx

%define INP_0 eax + 16*0
%define INP_1 eax + 16* 1
%define INP_2 eax + 16* 2
%define INP_3 eax + 16* 3
%define INP_4 eax + 16*4
%define INP_5 eax + 16*5
%define INP_6 eax + 16*6
%define INP_7 eax + 16*7

%define tg_1_16		(TABLEF + 0)
%define tg_2_16		(TABLEF + 8)
%define tg_3_16		(TABLEF + 16)
%define cos_4_16	(TABLEF + 24 )
%define ocos_4_16	(TABLEF + 32 )

%define OUT_0 ecx + 16*0
%define OUT_1 ecx + 16* 1
%define OUT_2 ecx + 16* 2
%define OUT_3 ecx + 16* 3
%define OUT_4 ecx + 16*4
%define OUT_5 ecx + 16*5
%define OUT_6 ecx + 16*6
%define OUT_7 ecx + 16*7

%define TABLE_0 ebx
%define TABLE_1 ebx + 64
%define TABLE_2 ebx + 128
%define TABLE_3 ebx + 192
%define TABLE_4 ebx + 256
%define TABLE_5 ebx + 320
%define TABLE_6 ebx + 384
%define TABLE_7 ebx + 448

%define x0 INP + 0* 16
%define x1 INP + 1* 16
%define x2 INP + 2* 16
%define x3 INP + 3* 16
%define x4 INP + 4* 16
%define x5 INP + 5* 16
%define x6 INP + 6* 16
%define x7 INP + 7* 16

%define y0 OUT + 0* 16
%define y1 OUT + 1* 16
%define y2 OUT + 2* 16
%define y3 OUT + 3* 16
%define y4 OUT + 4* 16
%define y5 OUT + 5* 16
%define y6 OUT + 6* 16
%define y7 OUT + 7* 16

%define BITS_FRW_ACC	3							; 2 or 3 for accuracy
%define SHIFT_FRW_COL	BITS_FRW_ACC
%define SHIFT_FRW_ROW	(BITS_FRW_ACC + 17)
%define RND_FRW_ROW		(1 << (SHIFT_FRW_ROW-1 ) )

SHIFT_FRW_ROW_CLIP2	equ (4 )
SHIFT_FRW_ROW_CLIP1	equ (SHIFT_FRW_ROW - SHIFT_FRW_ROW_CLIP2 )



SECTION .data

ALIGN 16

mmx_one times 4 dw 1
mmx_512 times 4 dw 512

one_corr times 4 dw 1

r_frw_row		 dd RND_FRW_ROW, RND_FRW_ROW

tg_all_16		 dw 13036, 13036, 13036, 13036,		; tg * (2<<16) + 0.5
				 dw 27146, 27146, 27146, 27146,		; tg * (2<<16) + 0.5
				 dw -21746, -21746, -21746, -21746,	; tg * (2<<16) + 0.5
				 dw -19195, -19195, -19195, -19195,	; cos * (2<<16) + 0.5
				 dw 23170, 23170, 23170, 23170  ; cos * (2<<15 ) + 0.5


tab_frw_01234567; FOR SSE or XMM
				; row0
				 dw 16384, 16384, 21407, -8867, ; w09 w01 w08 w00
				 dw 16384, 16384, 8867, -21407, ; w13 w05 w12 w04
                 dw 16384, -16384, 8867, 21407, ; w11 w03 w10 w02
                 dw -16384, 16384, -21407, -8867,; w15 w07 w14 w06
                 dw 22725, 12873, 19266, -22725,; w22 w20 w18 w16
                 dw 19266, 4520, -4520, -12873, ; w23 w21 w19 w17
                 dw 12873, 4520, 4520, 19266,   ; w30 w28 w26 w24
                 dw -22725, 19266, -12873, -22725,; w31 w29 w27 w25

				; row1
                 dw 22725, 22725, 29692, -12299,; w09 w01 w08 w00
                 dw 22725, 22725, 12299, -29692,; w13 w05 w12 w04
                 dw 22725, -22725, 12299, 29692,; w11 w03 w10 w02
                 dw -22725, 22725, -29692, -12299,; w15 w07 w14 w06
                 dw 31521, 17855, 26722, -31521,; w22 w20 w18 w16
                 dw 26722, 6270, -6270, -17855, ; w23 w21 w19 w17
                 dw 17855, 6270, 6270, 26722,   ; w30 w28 w26 w24
                 dw -31521, 26722, -17855, -31521,; w31 w29 w27 w25

				; row2
                 dw 21407, 21407, 27969, -11585,; w09 w01 w08 w00
                 dw 21407, 21407, 11585, -27969,; w13 w05 w12 w04
                 dw 21407, -21407, 11585, 27969,; w11 w03 w10 w02
                 dw -21407, 21407, -27969, -11585,	; w15 w07 w14 w06
                 dw 29692, 16819, 25172, -29692,; w22 w20 w18 w16
                 dw 25172, 5906, -5906, -16819, ; w23 w21 w19 w17
                 dw 16819, 5906, 5906, 25172,   ; w30 w28 w26 w24
                 dw -29692, 25172, -16819, -29692,; w31 w29 w27 w25

				; row3
                 dw 19266, 19266, 25172, -10426,; w09 w01 w08 w00
                 dw 19266, 19266, 10426, -25172,; w13 w05 w12 w04
                 dw 19266, -19266, 10426, 25172,; w11 w03 w10 w02
                 dw -19266, 19266, -25172, -10426,; w15 w07 w14 w06 
                 dw 26722, 15137, 22654, -26722,; w22 w20 w18 w16
                 dw 22654, 5315, -5315, -15137, ; w23 w21 w19 w17
                 dw 15137, 5315, 5315, 22654,   ; w30 w28 w26 w24
                 dw -26722, 22654, -15137, -26722,; w31 w29 w27 w25

				; row4
                 dw 16384, 16384, 21407, -8867, ; w09 w01 w08 w00
                 dw 16384, 16384, 8867, -21407, ; w13 w05 w12 w04
                 dw 16384, -16384, 8867, 21407, ; w11 w03 w10 w02
                 dw -16384, 16384, -21407, -8867,; w15 w07 w14 w06
                 dw 22725, 12873, 19266, -22725,; w22 w20 w18 w16
                 dw 19266, 4520, -4520, -12873, ; w23 w21 w19 w17
                 dw 12873, 4520, 4520, 19266,   ; w30 w28 w26 w24
                 dw -22725, 19266, -12873, -22725,; w31 w29 w27 w25 

				; row5
                 dw 19266, 19266, 25172, -10426,; w09 w01 w08 w00
                 dw 19266, 19266, 10426, -25172,; w13 w05 w12 w04
                 dw 19266, -19266, 10426, 25172,; w11 w03 w10 w02
                 dw -19266, 19266, -25172, -10426,; w15 w07 w14 w06
                 dw 26722, 15137, 22654, -26722,; w22 w20 w18 w16
                 dw 22654, 5315, -5315, -15137, ; w23 w21 w19 w17
                 dw 15137, 5315, 5315, 22654,   ; w30 w28 w26 w24
                 dw -26722, 22654, -15137, -26722,; w31 w29 w27 w25

				; row6
                 dw 21407, 21407, 27969, -11585,; w09 w01 w08 w00
                 dw 21407, 21407, 11585, -27969,; w13 w05 w12 w04
                 dw 21407, -21407, 11585, 27969,; w11 w03 w10 w02
                 dw -21407, 21407, -27969, -11585,; w15 w07 w14 w06
                 dw 29692, 16819, 25172, -29692,; w22 w20 w18 w16
                 dw 25172, 5906, -5906, -16819, ; w23 w21 w19 w17
                 dw 16819, 5906, 5906, 25172,   ; w30 w28 w26 w24
                 dw -29692, 25172, -16819, -29692,; w31 w29 w27 w25

				; row7
                 dw 22725, 22725, 29692, -12299,; w09 w01 w08 w00
                 dw 22725, 22725, 12299, -29692,; w13 w05 w12 w04
                 dw 22725, -22725, 12299, 29692,; w11 w03 w10 w02
                 dw -22725, 22725, -29692, -12299,; w15 w07 w14 w06
                 dw 31521, 17855, 26722, -31521,; w22 w20 w18 w16
                 dw 26722, 6270, -6270, -17855, ; w23 w21 w19 w17
                 dw 17855, 6270, 6270, 26722,   ; w30 w28 w26 w24
                 dw -31521, 26722, -17855, -31521; w31 w29 w27 w25



%macro fdct_one_row 3
    movd mm5, [%1+12]			; mm5 = 7 6

    punpcklwd mm5, [%1+8]

    movq mm2, mm5				; mm2 = 5 7 4 6
    psrlq mm5, 32				; mm5 = _ _ 5 7

    movq mm0, qword [%1]				; mm0 = 3 2 1 0
    punpcklwd mm5, mm2			; mm5 = 4 5 6 7

    movq mm1, mm0				; mm1 = 3 2 1 0
    paddsw mm0, mm5				; mm0 = [3+4, 2+5, 1+6, 0+7] ( xt3, xt2, xt1, xt0)

    psubsw mm1, mm5				; mm1 = [3-4, 2-5, 1-6, 0-7] ( xt7, xt6, xt5, xt4 )
    movq mm2, mm0				; mm2 = [ xt3 xt2 xt1 xt0 ]

    punpcklwd mm0, mm1			; mm0 = [ xt5 xt1 xt4 xt0 ]

    punpckhwd mm2, mm1			; mm2 = [ xt7 xt3 xt6 xt2 ]
    movq mm1, mm2				; mm1

	;//shuffle bytes around
    movq mm2, mm0				; 2; x3 x2 x1 x0

    movq mm3, qword [%2]				; 3; w06 w04 w02 w00
    punpcklwd mm0, mm1			; x5 x1 x4 x0

    movq mm5, mm0				; 5; x5 x1 x4 x0
    punpckldq mm0, mm0			; x4 x0 x4 x0  [ xt2 xt0 xt2 xt0 ]

    movq mm4, qword [%2+8]			; 4; w07 w05 w03 w01
    punpckhwd mm2, mm1			; 1; x7 x3 x6 x2

    pmaddwd mm3, mm0			; x4*w06+x0*w04 x4*w02+x0*w00
    movq mm6, mm2				; 6; x7 x3 x6 x2

    movq mm1, qword [%2+32]			; 1; w22 w20 w18 w16
    punpckldq mm2, mm2			; x6 x2 x6 x2  [ xt3 xt1 xt3 xt1 ]
	
    pmaddwd mm4, mm2			; x6*w07+x2*w05 x6*w03+x2*w01
    punpckhdq mm5, mm5			; x5 x1 x5 x1  [ xt6 xt4 xt6 xt4 ]

    pmaddwd mm0, qword [%2+16]		; x4*w14+x0*w12 x4*w10+x0*w08
    punpckhdq mm6, mm6			; x7 x3 x7 x3  [ xt7 xt5 xt7 xt5 ]

    movq mm7, qword [%2+40]			; 7; w23 w21 w19 w17
    pmaddwd mm1, mm5			; x5*w22+x1*w20 x5*w18+x1*w16

    paddd mm3, qword [round_frw_row]			; +rounder (y2,y0)
    pmaddwd mm7, mm6			; x7*w23+x3*w21 x7*w19+x3*w17

    pmaddwd mm2, qword [%2+24]		; x6*w15+x2*w13 x6*w11+x2*w09
    paddd mm3, mm4				; 4; a1=sum(even1 ) a0=sum(even0)

    pmaddwd mm5, qword [%2+48]		; x5*w30+x1*w28 x5*w26+x1*w24
 
    pmaddwd mm6, qword [%2+56]		; x7*w31+x3*w29 x7*w27+x3*w25
    paddd mm1, mm7				; 7; b1=sum(odd1 ) b0=sum(odd0)

    paddd mm0, qword [round_frw_row]			; +rounder (y6,y4 )
    psrad mm3, SHIFT_FRW_ROW_CLIP1; (y2, y0) 

    paddd mm1, qword [round_frw_row]			; +rounder (y3,y1 )
    paddd mm0, mm2				; 2; a3=sum(even3) a2=sum(even2 )

    paddd mm5, qword [round_frw_row]			; +rounder (y7,y5 )
    psrad mm1, SHIFT_FRW_ROW_CLIP1; y1=a1+b1 y0=a0+b0

    paddd mm5, mm6				; 6; b3=sum(odd3) b2=sum(odd2 )
    psrad mm0, SHIFT_FRW_ROW_CLIP1; y3=a3+b3 y2=a2+b2

    psrad mm5, SHIFT_FRW_ROW_CLIP1; y4=a3-b3 y5=a2-b2
	packssdw mm3, mm0			; 0; y6 y4 y2 y0, saturate {-32768,+32767}

    packssdw mm1, mm5			; 3; y7 y5 y3 y1, saturate {-32768,+32767}
    movq mm6, mm3				; mm0 = y6 y4 y2 y0

    punpcklwd mm3, mm1			; y3 y2 y1 y0
    punpckhwd mm6, mm1			; y7 y6 y5 y4

    psraw mm3, SHIFT_FRW_ROW_CLIP2; descale [y3 y2 y1 y0] to {-2048,+2047}

    psraw mm6, SHIFT_FRW_ROW_CLIP2; descale [y7 y6 y5 y4] to {-2048,+2047}

    movq [%3], mm3			; 1; save y3 y2 y1 y0
    movq [%3+8], mm6			; 7; save y7 y6 y5 y4
%endmacro

SECTION .text

;===========================================================================
;
;	uint32_t block_zero_mmx(short *block, 
;						uint32_t mask_sav,
;						uint32_t mask_var);
;
;	Author: David, Sigma Designs Inc.
;			04/04/ 2002
;
;===========================================================================
ALIGN 64
global _block_zero_mmx
_block_zero_mmx:
				push esi
			
				mov		esi, [esp+4+4]	; data_i
				pxor	mm7, mm7		; sav0

				movq	mm5, [mmx_512]	; 
				pxor	mm6, mm6		; var0

				add		esi, 32+4

				mov		ecx, 3
				movq	mm0, [esi]
				
				paddw	mm0, mm5		; add 512
				movq	mm4, mm5
				
				movq	mm1, mm0		; mm01 = data+512		

				psubusw mm1, mm5		; pixel-512 saturation
				psubusw mm4, mm0		; 512-pixel saturation

				add		esi, 16
				por		mm1, mm4				

				paddw	mm7, mm1		; mm7 = sav  = sigma |x|.
				
align 8				
.lp_var_sav
				; start next row with 4 data.
				movq	mm2, [esi]
				paddw	mm2, mm5		; add 512

				movq	mm4, mm5				
				movq	mm1, mm2		; mm23 = data+512		

				psubusw mm1, mm5		; pixel-512 saturation
				psubusw mm4, mm2		; 512-pixel saturation

				por		mm1, mm4				
				paddw	mm7, mm1		; mm7 = sav  = sigma |x|.

				; start to work on var0
				movq	mm5, mm2
				movq	mm4, mm0				
				movq	mm3, mm0

				psubusw	mm2, mm4
				psubusw	mm0, mm5

				por		mm0, mm2

				add		esi, 16
				paddw	mm6, mm0		; var0 stored!

				dec		ecx
				movq	mm0, mm3
				jnz		.lp_var_sav		;// looping ...

				movq	mm2, [esi]
				paddw	mm2, mm5

				movq	mm4, mm0				
				movq	mm5, mm2

				psubusw	mm2, mm4
				psubusw	mm0, mm5

				por		mm0, mm2

	;///////////////////////////////////////////////

				movq	mm3, [mmx_one]
				paddw	mm6, mm0		; var0 stored!

				pmaddwd mm7, mm3		; merge sum; mm3 = 1*4
				mov		ecx, [esp+4+8]; mask_sav

				pmaddwd mm6, mm3		; merge sum; mm3 = 1*4
				movq	mm5, mm7

				movq	mm4, mm6
				psrlq	mm5, 32 

				psrlq	mm4, 32 
				paddd	mm7, mm5		; mm7 = sav0

				paddd	mm6, mm4		; mm6 = var0
				movd	esi, mm7		; esi = sav0

				cmp		esi, ecx
				movd	eax, mm6		; edi = var0

				ja		.active
				mov		ecx, [esp+4+12]; mask_var
				cmp		eax, ecx

				ja		.active

				mov		eax, 1
				jmp		.done

.active
				xor		eax, eax				
.done

				pop		esi
				ret

;----------------------------------------------------------
;
; void fdct_mmx(short *block);
;
;----------------------------------------------------------
ALIGN 64
global _fdct8x8_mmx
_fdct8x8_mmx:
	
	push ebx

    mov INP, dword [esp + 8]	; block

    mov TABLEF, tg_all_16
    mov OUT, INP

mmx32_fdct_col103:
    movq mm0, [x1]				; 0; x1

    movq mm1, [x6]				; 1; x6
    movq mm2, mm0				; 2; x1

    movq mm3, [x2]				; 3; x2
    paddsw mm0, mm1				; t1 = x[1] + x[6]

    movq mm4, [x5]				; 4; x5
    psllw mm0, SHIFT_FRW_COL	; t1

    movq mm5, [x0]				; 5; x0
    paddsw mm4, mm3				; t2 = x[2] + x[5]

    paddsw mm5, [x7]			; t0 = x[0] + x[7]
    psllw mm4, SHIFT_FRW_COL	; t2

    movq mm6, mm0				; 6; t1
    psubsw mm2, mm1				; 1; t6 = x[1] - x[6]

    movq mm1, qword [tg_2_16]			; 1; tg_2_16
    psubsw mm0, mm4				; tm12 = t1 - t2

    movq mm7, [x3]				; 7; x3
    pmulhw mm1, mm0				; tm12*tg_2_16

    paddsw mm7, [x4]			; t3 = x[3] + x[4]
    psllw mm5, SHIFT_FRW_COL	; t0

    paddsw mm6, mm4				; 4; tp12 = t1 + t2
    psllw mm7, SHIFT_FRW_COL	; t3

    movq mm4, mm5				; 4; t0
    psubsw mm5, mm7				; tm03 = t0 - t3

    paddsw mm1, mm5				; y2 = tm03 + tm12*tg_2_16
    paddsw mm4, mm7				; 7; tp03 = t0 + t3

    por mm1, qword [one_corr]	; correction y2 +0.5
    psllw mm2, SHIFT_FRW_COL+1	; t6

    pmulhw mm5, qword [tg_2_16]		; tm03*tg_2_16
    movq mm7, mm4				; 7; tp03

    psubsw mm3, [x5]			; t5 = x[2] - x[5]
    psubsw mm4, mm6				; y4 = tp03 - tp12

    movq [y2], mm1				; 1; save y2
    paddsw mm7, mm6				; 6; y0 = tp03 + tp12
     
    movq mm1, [x3]				; 1; x3
    psllw mm3, SHIFT_FRW_COL+1	; t5

    psubsw mm1, [x4]			; t4 = x[3] - x[4]
    movq mm6, mm2				; 6; t6
    
    movq [y4], mm4				; 4; save y4
    paddsw mm2, mm3				; t6 + t5

    pmulhw mm2, qword [ocos_4_16]		; tp65 = ( t6 + t5 ) *cos_4_16
    psubsw mm6, mm3				; 3; t6 - t5

    pmulhw mm6, qword [ocos_4_16]		; tm65 = ( t6 - t5 ) *cos_4_16
    psubsw mm5, mm0				; 0; y6 = tm03*tg_2_16 - tm12

    por mm5, qword [one_corr]	; correction y6 +0.5
    psllw mm1, SHIFT_FRW_COL	; t4

    por mm2, qword [one_corr]	; correction tp65 +0.5
    movq mm4, mm1				; 4; t4

    movq mm3, [x0]				; 3; x0
    paddsw mm1, mm6				; tp465 = t4 + tm65

    psubsw mm3, [x7]			; t7 = x[0] - x[7]
    psubsw mm4, mm6				; 6; tm465 = t4 - tm65

    movq mm0, qword [tg_1_16]			; 0; tg_1_16
    psllw mm3, SHIFT_FRW_COL	; t7

    movq mm6, qword [tg_3_16]			; 6; tg_3_16
    pmulhw mm0, mm1				; tp465*tg_1_16

    movq [y0], mm7				; 7; save y0
    pmulhw mm6, mm4				; tm465*tg_3_16

    movq [y6], mm5				; 5; save y6
    movq mm7, mm3				; 7; t7

    movq mm5, qword [tg_3_16]			; 5; tg_3_16
    psubsw mm7, mm2				; tm765 = t7 - tp65

    paddsw mm3, mm2				; 2; tp765 = t7 + tp65
    pmulhw mm5, mm7				; tm765*tg_3_16

    paddsw mm0, mm3				; y1 = tp765 + tp465*tg_1_16
    paddsw mm6, mm4				; tm465*tg_3_16

    pmulhw mm3, qword [tg_1_16]		; tp765*tg_1_16
 	
    por mm0, qword [one_corr]	; correction y1 +0.5
    paddsw mm5, mm7				; tm765*tg_3_16

    psubsw mm7, mm6				; 6; y3 = tm765 - tm465*tg_3_16
    add INP, 0x08				;// increment pointer

    movq [y1], mm0				; 0; save y1
    paddsw mm5, mm4				; 4; y5 = tm765*tg_3_16 + tm465

    movq [y3], mm7				; 7; save y3
    psubsw mm3, mm1				; 1; y7 = tp765*tg_1_16 - tp465

    movq [y5], mm5				; 5; save y5

mmx32_fdct_col47:				; begin processing column 4-7
    movq mm0, [x1]				; 0; x1

    movq [y7], mm3				; 3; save y7 ( columns 0-4 )

    movq mm1, [x6]				; 1; x6
    movq mm2, mm0				; 2; x1

    movq mm3, [x2]				; 3; x2
    paddsw mm0, mm1				; t1 = x[1] + x[6]

    movq mm4, [x5]				; 4; x5
    psllw mm0, SHIFT_FRW_COL	; t1

    movq mm5, [x0]				; 5; x0
    paddsw mm4, mm3				; t2 = x[2] + x[5]

    paddsw mm5, [x7]			; t0 = x[0] + x[7]
    psllw mm4, SHIFT_FRW_COL	; t2
	
    movq mm6, mm0				; 6; t1
    psubsw mm2, mm1				; 1; t6 = x[1] - x[6]

    movq mm1, qword [tg_2_16]			; 1; tg_2_16
    psubsw mm0, mm4				; tm12 = t1 - t2

    movq mm7, [x3]				; 7; x3
    pmulhw mm1, mm0				; tm12*tg_2_16

    paddsw mm7, [x4]			; t3 = x[3] + x[4]
    psllw mm5, SHIFT_FRW_COL	; t0

    paddsw mm6, mm4				; 4; tp12 = t1 + t2
    psllw mm7, SHIFT_FRW_COL	; t3

    movq mm4, mm5				; 4; t0
    psubsw mm5, mm7				; tm03 = t0 - t3

    paddsw mm1, mm5				; y2 = tm03 + tm12*tg_2_16
    paddsw mm4, mm7				; 7; tp03 = t0 + t3

    por mm1, qword [one_corr]	; correction y2 +0.5
    psllw mm2, SHIFT_FRW_COL+1	; t6

    pmulhw mm5, qword [tg_2_16]		; tm03*tg_2_16
    movq mm7, mm4				; 7; tp03

    psubsw mm3, [x5]			; t5 = x[2] - x[5]
    psubsw mm4, mm6				; y4 = tp03 - tp12

    movq [y2+8], mm1			; 1; save y2
    paddsw mm7, mm6				; 6; y0 = tp03 + tp12
     
    movq mm1, [x3]				; 1; x3
    psllw mm3, SHIFT_FRW_COL+1; t5

    psubsw mm1, [x4]			; t4 = x[3] - x[4]
    movq mm6, mm2				; 6; t6
    
    movq [y4+8], mm4			; 4; save y4
    paddsw mm2, mm3				; t6 + t5

    pmulhw mm2, qword [ocos_4_16]		; tp65 = ( t6 + t5 ) *cos_4_16
    psubsw mm6, mm3				; 3; t6 - t5

    pmulhw mm6, qword [ocos_4_16]		; tm65 = ( t6 - t5 ) *cos_4_16
    psubsw mm5, mm0				; 0; y6 = tm03*tg_2_16 - tm12

    por mm5, qword [one_corr]	; correction y6 +0.5
    psllw mm1, SHIFT_FRW_COL	; t4

    por mm2, qword [one_corr]	; correction tp65 +0.5
    movq mm4, mm1				; 4; t4

    movq mm3, [x0]				; 3; x0
    paddsw mm1, mm6				; tp465 = t4 + tm65

    psubsw mm3, [x7]			; t7 = x[0] - x[7]
    psubsw mm4, mm6				; 6; tm465 = t4 - tm65

    movq mm0, qword [tg_1_16]			; 0; tg_1_16
    psllw mm3, SHIFT_FRW_COL	; t7

    movq mm6, qword [tg_3_16]			; 6; tg_3_16
    pmulhw mm0, mm1				; tp465*tg_1_16

    movq [y0+8], mm7			; 7; save y0
    pmulhw mm6, mm4				; tm465*tg_3_16

    movq [y6+8], mm5			; 5; save y6
    movq mm7, mm3				; 7; t7

    movq mm5, qword [tg_3_16]			; 5; tg_3_16
    psubsw mm7, mm2				; tm765 = t7 - tp65

    paddsw mm3, mm2				; 2; tp765 = t7 + tp65
    pmulhw mm5, mm7				; tm765*tg_3_16

    paddsw mm0, mm3				; y1 = tp765 + tp465*tg_1_16
    paddsw mm6, mm4				; tm465*tg_3_16

    pmulhw mm3, [tg_1_16]		; tp765*tg_1_16
    
	por mm0, qword [one_corr]	; correction y1 +0.5
    paddsw mm5, mm7				; tm765*tg_3_16
	
    psubsw mm7, mm6				; 6; y3 = tm765 - tm465*tg_3_16
 
    movq [y1+8], mm0			; 0; save y1
    paddsw mm5, mm4				; 4; y5 = tm765*tg_3_16 + tm465

    movq [y3+8], mm7			; 7; save y3
    psubsw mm3, mm1				; 1; y7 = tp765*tg_1_16 - tp465

    movq [y5+8], mm5			; 5; save y5

    movq [y7+8], mm3			; 3; save y7
	
	mov INP, [esp + 8]			; row 0

	lea TABLEF, [tab_frw_01234567]	; row 0	;!!!
	mov OUT, INP

	lea round_frw_row, [r_frw_row]	; !!!

;//lp_mmx_fdct_row1:
	fdct_one_row INP_0, TABLE_0, OUT_0
	fdct_one_row INP_1, TABLE_1, OUT_1
	fdct_one_row INP_2, TABLE_2, OUT_2
	fdct_one_row INP_3, TABLE_3, OUT_3
	fdct_one_row INP_4, TABLE_4, OUT_4
	fdct_one_row INP_5, TABLE_5, OUT_5
	fdct_one_row INP_6, TABLE_6, OUT_6
	fdct_one_row INP_7, TABLE_7, OUT_7

	pop ebx
	;emms						; all emms will be done after the frame processing.
	
	ret

