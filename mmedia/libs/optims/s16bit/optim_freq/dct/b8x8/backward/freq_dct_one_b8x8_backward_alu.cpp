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
#include "mmedia/dlls/codecs/codec_funcs/codec-funcs-const-vals.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
/*
 * jidctflt.c
 *
 * Copyright (C) 1994-1998, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a floating-point implementation of the
 * inverse DCT (Discrete Cosine Transform).  In the IJG code, this routine
 * must also perform dequantization of the input coefficients.
 *
 * This implementation should be more accurate than either of the integer
 * IDCT implementations.  However, it may not give the same results on all
 * machines because of differences in roundoff behavior.  Speed will depend
 * on the hardware's floating point capacity.
 *
 * A 2-D IDCT can be done by 1-D IDCT on each column followed by 1-D IDCT
 * on each row (or vice versa, but it's more convenient to emit a row at
 * a time ).  Direct algorithms are also available, but they are much more
 * complex and seem not to be any faster when reduced to code.
 *
 * This implementation is based on Arai, Agui, and Nakajima's algorithm for
 * scaled DCT.  Their original paper (Trans. IEICE E-71(11 ):1095 ) is in
 * Japanese, but the algorithm is described in the Pennebaker & Mitchell
 * JPEG textbook (see REFERENCES section in file README).  The following code
 * is based directly on figure 4-8 in P&M.
 * While an 8-point DCT cannot be done in less than 11 multiplies, it is
 * possible to arrange the computation so that many of the multiplies are
 * simple scalings of the final outputs.  These multiplies can then be
 * folded into the multiplications or divisions by the JPEG quantization
 * table entries.  The AA&N method leaves only 5 multiplies and 29 adds
 * to be done in the DCT itself.
 * The primary disadvantage of this method is that with a fixed-point
 * implementation, accuracy is lost due to imprecise representation of the
 * scaled quantization values.  However, that problem does not arise if
 * we use floating point arithmetic.
 */

#define DCT_FLOAT_SUPPORTED
#define RIGHT_SHIFT_IS_UNSIGNED
#define DCTSIZE 8
#define INT32 int
#define DCTELEM short

typedef float        fast_float;
typedef float        FAST_FLOAT;
typedef FAST_FLOAT   FLOAT_MULT_TYPE; /* preferred floating type */
typedef std::int16_t JCOEF;


#define DCTSIZE 8           /* The basic DCT block is 8x8 samples */
#define DCTSIZE2 64         /* DCTSIZE squared; # of elements in a block */
#define NUM_QUANT_TBLS 4    /* Quantization tables are numbered 0..3 */
#define NUM_HUFF_TBLS 4     /* Huffman tables are numbered 0..3 */
#define NUM_ARITH_TBLS 16   /* Arith-coding tables are numbered 0..15 */
#define MAX_COMPS_IN_SCAN 4 /* JPEG limit on # of components in one scan */
#define MAX_SAMP_FACTOR 4   /* JPEG limit on sampling factors */
/* Unfortunately, some bozo at Adobe saw no reason to be bound by the standard;
 * the PostScript DCT filter can emit files with many more than 10 blocks/MCU.
 * If you happen to run across such a file, you can up D_MAX_BLOCKS_IN_MCU
 * to handle it.  We even let you do this from the jconfig.h file.  However,
 * we strongly discourage changing C_MAX_BLOCKS_IN_MCU; just because Adobe
 * sometimes emits noncompliant files doesn't mean you should too.
 */
#define C_MAX_BLOCKS_IN_MCU 10 /* compressor's limit on blocks per MCU */
#ifndef D_MAX_BLOCKS_IN_MCU
#  define D_MAX_BLOCKS_IN_MCU 10 /* decompressor's limit on blocks per MCU */
#endif


typedef std::uint8_t JSAMPLE;
typedef JSAMPLE*     JSAMPROW;   /* ptr to one image row of pixel samples. */
typedef JSAMPROW*    JSAMPARRAY; /* ptr to some rows ( a 2-D sample array) */
typedef JSAMPARRAY*  JSAMPIMAGE; /* a 3-D sample array: top index is color */

typedef JCOEF        JBLOCK[DCTSIZE2]; /* one block of coefficients */
typedef JBLOCK*      JBLOCKROW;        /* pointer to one row of coefficient blocks */
typedef JBLOCKROW*   JBLOCKARRAY;      /* a 2-D array of coefficient blocks */
typedef JBLOCKARRAY* JBLOCKIMAGE;      /* a 3-D array of coefficient blocks */

typedef JCOEF* JCOEFPTR; /* useful in a couple of places */


#ifdef RIGHT_SHIFT_IS_UNSIGNED
#  define ISHIFT_TEMPS DCTELEM ishift_temp;
#  if BITS_IN_JSAMPLE == 8
#    define DCTELEMBITS 16 /* DCTELEM may be 16 or 32 bits */
#  else
#    define DCTELEMBITS 32 /* DCTELEM must be 32 bits */
#  endif
#  define IRIGHT_SHIFT(x, shft) \
    ((ishift_temp = (x)) < 0 ? (ishift_temp >> (shft)) | ((~((DCTELEM) 0)) << (DCTELEMBITS - (shft))) : (ishift_temp >> (shft)))
#else
#  define ISHIFT_TEMPS
#  define IRIGHT_SHIFT(x, shft) ((x) >> (shft))
#endif

#ifdef USE_ACCURATE_ROUNDING
#  define IDESCALE(x, n) ((int) IRIGHT_SHIFT ((x) + (1 << ((n) - 1)), n))
#else
#  define IDESCALE(x, n) ((int) IRIGHT_SHIFT (x, n))
#endif

#ifdef DCT_FLOAT_SUPPORTED


/*
 * This module is specialized to the case DCTSIZE = 8.
 */

#  if DCTSIZE != 8
Sorry, this code only copes with 8x8 DCTs./* deliberate syntax err */
#  endif


/* Dequantize a coefficient by multiplying it by the multiplier-table
 * entry; produce a float result.
 */

#  define DEQUANTIZE(coef, quantval) (((fast_float) (coef)) * (quantval))


       /*
        * Perform dequantization and inverse DCT on one block of coefficients.
        */

       void
       alu_b8x8_float (std::int16_t* blk)
// j_decompress_ptr cinfo,
//                    jpeg_component_info * compptr,
//                      JCOEFPTR coef_block,
//                     JSAMPARRAY output_buf,
//               JDIMENSION output_col )
{
#  if 0
  fast_float tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  fast_float tmp10, tmp11, tmp12, tmp13;
  fast_float z5, z10, z11, z12, z13;
  JCOEFPTR inptr;
  FLOAT_MULT_TYPE * quantptr;
  fast_float * wsptr;
  JSAMPROW outptr;
  JSAMPLE *range_limit = IDCT_range_limit( cinfo );
  int ctr;
  fast_float workspace[DCTSIZE2]; /* bufs data between passes */
  SHIFT_TEMPS

/* Pass 1: process columns from input, store into work array. */

  inptr = coef_block;
  quantptr = (FLOAT_MULT_TYPE *) compptr->dct_table;
  wsptr = workspace;

  for ( ctr = DCTSIZE; ctr > 0; ctr--) 
  {
    U3_ASSERT_SIGNAL( "failed" );
#    if 0
    /* Due to quantization, we will usually find that many of the input
     * coefficients are zero, especially the AC terms.  We can exploit this
     * by short-circuiting the IDCT calculation for any column in which all
     * the AC terms are zero.  In that case each output is equal to the
     * DC coefficient (with scale factor as needed).
     * With typical images and quantization tables, half or more of the
     * column DCT calculations can be simplified this way.
     */
    
    if (inptr[DCTSIZE* 1] == 0 && inptr[DCTSIZE* 2] == 0 &&
  inptr[DCTSIZE* 3] == 0 && inptr[DCTSIZE*4] == 0 &&
  inptr[DCTSIZE*5] == 0 && inptr[DCTSIZE*6] == 0 &&
  inptr[DCTSIZE*7] == 0) {
      /* AC terms all zero */
      fast_float dcval = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0] );
      
      wsptr[DCTSIZE*0] = dcval;
      wsptr[DCTSIZE* 1] = dcval;
      wsptr[DCTSIZE* 2] = dcval;
      wsptr[DCTSIZE* 3] = dcval;
      wsptr[DCTSIZE*4] = dcval;
      wsptr[DCTSIZE*5] = dcval;
      wsptr[DCTSIZE*6] = dcval;
      wsptr[DCTSIZE*7] = dcval;
      
      inptr++;      /* advance pointers to next column */
      quantptr++;
      wsptr++;
      continue;
    }
#    endif
    /* Even part */

    tmp0 = DEQUANTIZE(inptr[DCTSIZE*0], quantptr[DCTSIZE*0] );
    tmp1 = DEQUANTIZE(inptr[DCTSIZE* 2], quantptr[DCTSIZE* 2] );
    tmp2 = DEQUANTIZE(inptr[DCTSIZE*4], quantptr[DCTSIZE*4] );
    tmp3 = DEQUANTIZE(inptr[DCTSIZE*6], quantptr[DCTSIZE*6] );

    tmp10 = tmp0 + tmp2;  /* phase 3 */
    tmp11 = tmp0 - tmp2;

    tmp13 = tmp1 + tmp3;  /* phases 5-3 */
    tmp12 = ( tmp1 - tmp3) * ( (fast_float ) 1.414213562 ) - tmp13; /* 2*c4 */

    tmp0 = tmp10 + tmp13; /* phase 2 */
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;
    
    /* Odd part */

    tmp4 = DEQUANTIZE(inptr[DCTSIZE* 1], quantptr[DCTSIZE* 1] );
    tmp5 = DEQUANTIZE(inptr[DCTSIZE* 3], quantptr[DCTSIZE* 3] );
    tmp6 = DEQUANTIZE(inptr[DCTSIZE*5], quantptr[DCTSIZE*5] );
    tmp7 = DEQUANTIZE(inptr[DCTSIZE*7], quantptr[DCTSIZE*7] );

    z13 = tmp6 + tmp5;    /* phase 6 */
    z10 = tmp6 - tmp5;
    z11 = tmp4 + tmp7;
    z12 = tmp4 - tmp7;

    tmp7 = z11 + z13;   /* phase 5 */
    tmp11 = (z11 - z13) * ( (fast_float ) 1.414213562 ); /* 2*c4 */

    z5 = (z10 + z12 ) * ( (fast_float ) 1.847759065 ); /* 2*c2 */
    tmp10 = ( (fast_float ) 1.082392200) * z12 - z5; /* 2*( c2-c6) */
    tmp12 = ( (fast_float ) -2.613125930) * z10 + z5; /* -2*( c2+c6) */

    tmp6 = tmp12 - tmp7;  /* phase 2 */
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    wsptr[DCTSIZE*0] = tmp0 + tmp7;
    wsptr[DCTSIZE*7] = tmp0 - tmp7;
    wsptr[DCTSIZE* 1] = tmp1 + tmp6;
    wsptr[DCTSIZE*6] = tmp1 - tmp6;
    wsptr[DCTSIZE* 2] = tmp2 + tmp5;
    wsptr[DCTSIZE*5] = tmp2 - tmp5;
    wsptr[DCTSIZE*4] = tmp3 + tmp4;
    wsptr[DCTSIZE* 3] = tmp3 - tmp4;

    inptr++;      /* advance pointers to next column */
    quantptr++;
    wsptr++;
  }
  
  /* Pass 2: process rows from work array, store into output array. */
  /* Note that we must descale the results by a factor of 8 == 2** 3. */

  wsptr = workspace;
  for ( ctr = 0; ctr < DCTSIZE; ctr++) {
    outptr = output_buf[ctr] + output_col;
    /* Rows of zeroes can be exploited in the same way as we did with columns.
     * However, the column calculation has created many nonzero AC terms, so
     * the simplification applies less often ( typically 5% to 10% of the time ).
     * And testing floats for zero is relatively expensive, so we don't bother.
     */
    
    /* Even part */

    tmp10 = wsptr[0] + wsptr[4];
    tmp11 = wsptr[0] - wsptr[4];

    tmp13 = wsptr[2] + wsptr[6];
    tmp12 = (wsptr[2] - wsptr[6] ) * ( (fast_float ) 1.414213562 ) - tmp13;

    tmp0 = tmp10 + tmp13;
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;

    /* Odd part */

    z13 = wsptr[5] + wsptr[3];
    z10 = wsptr[5] - wsptr[3];
    z11 = wsptr[1] + wsptr[7];
    z12 = wsptr[1] - wsptr[7];

    tmp7 = z11 + z13;
    tmp11 = (z11 - z13) * ( (fast_float ) 1.414213562 );

    z5 = (z10 + z12 ) * ( (fast_float ) 1.847759065 ); /* 2*c2 */
    tmp10 = ( (fast_float ) 1.082392200) * z12 - z5; /* 2*( c2-c6) */
    tmp12 = ( (fast_float ) -2.613125930) * z10 + z5; /* -2*( c2+c6) */

    tmp6 = tmp12 - tmp7;
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    /* Final output stage: scale down by a factor of 8 and range-limit */

    outptr[0] = range_limit[(int ) DESCALE( (INT32 ) ( tmp0 + tmp7), 3)
          & RANGE_MASK];
    outptr[7] = range_limit[(int ) DESCALE( (INT32 ) ( tmp0 - tmp7), 3)
          & RANGE_MASK];
    outptr[1] = range_limit[(int ) DESCALE( (INT32 ) ( tmp1 + tmp6), 3)
          & RANGE_MASK];
    outptr[6] = range_limit[(int ) DESCALE( (INT32 ) ( tmp1 - tmp6), 3)
          & RANGE_MASK];
    outptr[2] = range_limit[(int ) DESCALE( (INT32 ) ( tmp2 + tmp5 ), 3)
          & RANGE_MASK];
    outptr[5] = range_limit[(int ) DESCALE( (INT32 ) ( tmp2 - tmp5 ), 3)
          & RANGE_MASK];
    outptr[4] = range_limit[(int ) DESCALE( (INT32 ) ( tmp3 + tmp4 ), 3)
          & RANGE_MASK];
    outptr[3] = range_limit[(int ) DESCALE( (INT32 ) ( tmp3 - tmp4 ), 3)
          & RANGE_MASK];
    
    wsptr += DCTSIZE;   /* advance pointer to next row */
  }
#  endif
}

#endif /* DCT_FLOAT_SUPPORTED */


void
alu_b8x8 (std::int16_t* blk)
{
  // alu_b8x8_float ( blk );
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward
