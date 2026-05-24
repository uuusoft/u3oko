/**
\file       freq_dct_one_b8x8_forward_alu.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_forward.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
/*
 * jfdctfst.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a fast, not so accurate integer implementation of the
 * forward DCT (Discrete Cosine Transform).
 *
 * A 2-D DCT can be done by 1-D DCT on each row followed by 1-D DCT
 * on each column.  Direct algorithms are also available, but they are
 * much more complex and seem not to be any faster when reduced to code.
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
 * The primary disadvantage of this method is that with fixed-point math,
 * accuracy is lost due to imprecise representation of the scaled
 * quantization values.  The smaller the quantization table entry, the less
 * precise the scaled value, so this implementation does worse with high-
 * quality-setting files than with low-quality ones.
 */

#define DCTSIZE 8
#define INT32 int
#define DCTELEM short
// #define RIGHT_SHIFT_IS_UNSIGNED


/* We assume that right shift corresponds to signed division by 2 with
 * rounding towards minus infinity.  This is correct for typical "arithmetic
 * shift" instructions that shift in copies of the sign bit.  But some
 * C compilers implement >> with an unsigned shift.  For these machines you
 * must define RIGHT_SHIFT_IS_UNSIGNED.
 * RIGHT_SHIFT provides a proper signed right shift of an INT32 quantity.
 * It is only applied with constant shift counts.  SHIFT_TEMPS must be
 * included in the variables of any routine using RIGHT_SHIFT.
 */

#ifdef RIGHT_SHIFT_IS_UNSIGNED
#  define SHIFT_TEMPS INT32 shift_temp;
#  define RIGHT_SHIFT(x, shft) \
    ((shift_temp = (x)) < 0 ? (shift_temp >> (shft)) | ((~((INT32) 0)) << (32 - (shft))) : (shift_temp >> (shft)))
#else
#  define SHIFT_TEMPS
#  define RIGHT_SHIFT(x, shft) ((x) >> (shft))
#endif


/*
 * This module is specialized to the case DCTSIZE = 8.
 */

#if DCTSIZE != 8
Sorry, this code only copes with 8x8 DCTs./* deliberate syntax err */
#endif


/* Scaling decisions are generally the same as in the LL&M algorithm;
 * see jfdctint.c for more details.  However, we choose to descale
 * (right shift ) multiplication products as soon as they are formed,
 * rather than carrying additional fractional bits into subsequent additions.
 * This compromises accuracy slightly, but it lets us save a few shifts.
 * More importantly, 16-bit arithmetic is then adequate (for 8-bit samples)
 * everywhere except in the multiplications proper; this saves a good deal
 * of work on 16-bit-int machines.
 *
 * Again to save a few shifts, the intermediate results between pass 1 and
 * pass 2 are not upscaled, but are represented only to integral precision.
 *
 * A final compromise is to represent the multiplicative constants to only
 * 8 fractional bits, rather than 13.  This saves some shifting work on some
 * machines, and may also reduce the cost of multiplication (since there
 * are fewer one-bits in the constants).
 */

#define CONST_BITS 8


/* Some C compilers fail to reduce "FIX( constant )" at compile time, thus
 * causing a lot of useless floating-point operations at run time.
 * To get around this we use the following pre-calculated constants.
 * If you change CONST_BITS you may want to add appropriate values.
 * (With a reasonable C compiler, you can just rely on the FIX() macro...)
 */

#if CONST_BITS == 8
#  define FIX_0_382683433 ((INT32) 98)  /* FIX(0.382683433) */
#  define FIX_0_541196100 ((INT32) 139) /* FIX(0.541196100) */
#  define FIX_0_707106781 ((INT32) 181) /* FIX(0.707106781 ) */
#  define FIX_1_306562965 ((INT32) 334) /* FIX(1.306562965 ) */
#else
#  define FIX_0_382683433 FIX (0.382683433)
#  define FIX_0_541196100 FIX (0.541196100)
#  define FIX_0_707106781 FIX (0.707106781)
#  define FIX_1_306562965 FIX (1.306562965)
#endif


/* We can gain a little more speed, with a further compromise in accuracy,
 * by omitting the addition in a descaling shift.  This yields an incorrectly
 * rounded result half the time...
 */

#ifndef USE_ACCURATE_ROUNDING
#  undef DESCALE
#  define DESCALE(x, n) RIGHT_SHIFT (x, n)
#endif


/* Multiply a DCTELEM variable by an INT32 constant, and immediately
 * descale to yield a DCTELEM result.
 */

#define MULTIPLY(var, const) ((DCTELEM) DESCALE ((var) * (const), CONST_BITS))


       /*
        * Perform the forward DCT on one block of samples.
        */

       void
       alu_int (DCTELEM* data)
{
  DCTELEM  tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  DCTELEM  tmp10, tmp11, tmp12, tmp13;
  DCTELEM  z1, z2, z3, z4, z5, z11, z13;
  DCTELEM* dataptr;
  int      ctr;
  SHIFT_TEMPS

  /* Pass 1: process rows. */

  dataptr = data;
  for (ctr = DCTSIZE - 1; ctr >= 0; ctr--)
  {
    tmp0 = dataptr[0] + dataptr[7];
    tmp7 = dataptr[0] - dataptr[7];
    tmp1 = dataptr[1] + dataptr[6];
    tmp6 = dataptr[1] - dataptr[6];
    tmp2 = dataptr[2] + dataptr[5];
    tmp5 = dataptr[2] - dataptr[5];
    tmp3 = dataptr[3] + dataptr[4];
    tmp4 = dataptr[3] - dataptr[4];

    /* Even part */

    tmp10 = tmp0 + tmp3; /* phase 2 */
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    dataptr[0] = tmp10 + tmp11; /* phase 3 */
    dataptr[4] = tmp10 - tmp11;

    z1         = MULTIPLY (tmp12 + tmp13, FIX_0_707106781); /* c4 */
    dataptr[2] = tmp13 + z1;                                /* phase 5 */
    dataptr[6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5; /* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = MULTIPLY (tmp10 - tmp12, FIX_0_382683433); /* c6 */
    z2 = MULTIPLY (tmp10, FIX_0_541196100) + z5;    /* c2-c6 */
    z4 = MULTIPLY (tmp12, FIX_1_306562965) + z5;    /* c2+c6 */
    z3 = MULTIPLY (tmp11, FIX_0_707106781);         /* c4 */

    z11 = tmp7 + z3; /* phase 5 */
    z13 = tmp7 - z3;

    dataptr[5] = z13 + z2; /* phase 6 */
    dataptr[3] = z13 - z2;
    dataptr[1] = z11 + z4;
    dataptr[7] = z11 - z4;

    dataptr += DCTSIZE; /* advance pointer to next row */
  }

  /* Pass 2: process columns. */

  dataptr = data;
  for (ctr = DCTSIZE - 1; ctr >= 0; ctr--)
  {
    tmp0 = dataptr[DCTSIZE * 0] + dataptr[DCTSIZE * 7];
    tmp7 = dataptr[DCTSIZE * 0] - dataptr[DCTSIZE * 7];
    tmp1 = dataptr[DCTSIZE * 1] + dataptr[DCTSIZE * 6];
    tmp6 = dataptr[DCTSIZE * 1] - dataptr[DCTSIZE * 6];
    tmp2 = dataptr[DCTSIZE * 2] + dataptr[DCTSIZE * 5];
    tmp5 = dataptr[DCTSIZE * 2] - dataptr[DCTSIZE * 5];
    tmp3 = dataptr[DCTSIZE * 3] + dataptr[DCTSIZE * 4];
    tmp4 = dataptr[DCTSIZE * 3] - dataptr[DCTSIZE * 4];

    /* Even part */

    tmp10 = tmp0 + tmp3; /* phase 2 */
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    dataptr[DCTSIZE * 0] = tmp10 + tmp11; /* phase 3 */
    dataptr[DCTSIZE * 4] = tmp10 - tmp11;

    z1                   = MULTIPLY (tmp12 + tmp13, FIX_0_707106781); /* c4 */
    dataptr[DCTSIZE * 2] = tmp13 + z1;                                /* phase 5 */
    dataptr[DCTSIZE * 6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5; /* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = MULTIPLY (tmp10 - tmp12, FIX_0_382683433); /* c6 */
    z2 = MULTIPLY (tmp10, FIX_0_541196100) + z5;    /* c2-c6 */
    z4 = MULTIPLY (tmp12, FIX_1_306562965) + z5;    /* c2+c6 */
    z3 = MULTIPLY (tmp11, FIX_0_707106781);         /* c4 */

    z11 = tmp7 + z3; /* phase 5 */
    z13 = tmp7 - z3;

    dataptr[DCTSIZE * 5] = z13 + z2; /* phase 6 */
    dataptr[DCTSIZE * 3] = z13 - z2;
    dataptr[DCTSIZE * 1] = z11 + z4;
    dataptr[DCTSIZE * 7] = z11 - z4;

    dataptr++; /* advance pointer to next column */
  }
}


void
alu_b8x8 (std::int16_t* buf)
{
#if 1
  alu_int (buf);
#else
  int tbuf[64];
  std::copy (buf, buf + 64, tbuf);
  alu_int (tbuf);
  std::copy (tbuf, tbuf + 64, buf);
#endif
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward
