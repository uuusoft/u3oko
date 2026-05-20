/*
 * jfdctflt.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a floating-point implementation of the
 * forward DCT (Discrete Cosine Transform).
 *
 * This implementation should be more accurate than either of the integer
 * DCT implementations.  However, it may not give the same results on all
 * machines because of differences in roundoff behavior.  Speed will depend
 * on the hardware's floating point capacity.
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
 * The primary disadvantage of this method is that with a fixed-point
 * implementation, accuracy is lost due to imprecise representation of the
 * scaled quantization values.  However, that problem does not arise if
 * we use floating point arithmetic.
 */
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../codec-funcs-includes_int.hpp"
#include "../../codec-funcs-const-vals.hpp"

namespace dlls::codecs::dct
{
/*
  Общие рассчет для черно-белого полукадра
  Примерный рассчет числа операций на один блок
  +   -   [ 8 * 18 + 8 * 19 ] = 296
  -   -   [ 8 * 12 + 8 * 13 ] = 200
  *   -   [ 8 * 5 + 8 * 28 ]  = 248
  /   -   [ 0 ]               = 0

  на полукадр
  +   -   [ 296 * 3456 ]      = 1022976
  -   -   [ 200 * 3456 ]      = 691200
  *   -   [ 248 * 3456 ]      = 857088
  /   -   [ 0   * 3456 ]      = 0

  Для П4-1.7 операций в секунду
  +   -   180 000 000 - 175 кадров в секунду
  -   -   180 000 000 - 260
  *   -   180 000 000 - 210
  /   -   50  000 000 -

  Интегральный показатель для П4 -
  1.0 / ( ( 1022976 / 180 000 000 ) + ( 691200 / 180 000 000 ) + ( 857088 / 180 000 000 ) ) = 1.0 / 0.0142848 = 70 кадров
*/
bool
jpeg_fdct_float (float *data)
{
  float  tmp0 = 0.0, tmp1 = 0.0, tmp2 = 0.0, tmp3 = 0.0, tmp4 = 0.0, tmp5 = 0.0, tmp6 = 0.0, tmp7 = 0.0;
  float  tmp10 = 0.0, tmp11 = 0.0, tmp12 = 0.0, tmp13 = 0.0;
  float  z1 = 0.0, z2 = 0.0, z3 = 0.0, z4 = 0.0, z5 = 0.0, z11 = 0.0, z13 = 0.0;
  float *dataptr = 0;
  int    ctr     = 0;

  /* Pass 1: process rows. */

  dataptr = data;

  for (ctr = 7; ctr >= 0; ctr--)
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

    z1         = (tmp12 + tmp13) * ((float) 0.707106781); /* c4 */
    dataptr[2] = tmp13 + z1;                              /* phase 5 */
    dataptr[6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5; /* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = (tmp10 - tmp12) * ((float) 0.382683433); /* c6 */
    z2 = ((float) 0.541196100) * tmp10 + z5;      /* c2-c6 */
    z4 = ((float) 1.306562965) * tmp12 + z5;      /* c2+c6 */
    z3 = tmp11 * ((float) 0.707106781);           /* c4 */

    z11 = tmp7 + z3; /* phase 5 */
    z13 = tmp7 - z3;

    dataptr[5] = z13 + z2; /* phase 6 */
    dataptr[3] = z13 - z2;
    dataptr[1] = z11 + z4;
    dataptr[7] = z11 - z4;

    dataptr += ::dlls::codecs::consts::dim_elements_macroblock; /* advance pointer to next row */
  }

  /* Pass 2: process columns. */

  dataptr = data;
  for (ctr = 7; ctr >= 0; ctr--)
  {
    tmp0 = dataptr[8 * 0] + dataptr[8 * 7];
    tmp7 = dataptr[8 * 0] - dataptr[8 * 7];
    tmp1 = dataptr[8 * 1] + dataptr[8 * 6];
    tmp6 = dataptr[8 * 1] - dataptr[8 * 6];
    tmp2 = dataptr[8 * 2] + dataptr[8 * 5];
    tmp5 = dataptr[8 * 2] - dataptr[8 * 5];
    tmp3 = dataptr[8 * 3] + dataptr[8 * 4];
    tmp4 = dataptr[8 * 3] - dataptr[8 * 4];

    /* Even part */

    tmp10 = tmp0 + tmp3; /* phase 2 */
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    dataptr[8 * 0] = tmp10 + tmp11; /* phase 3 */
    dataptr[8 * 4] = tmp10 - tmp11;

    z1             = (tmp12 + tmp13) * ((float) 0.707106781); /* c4 */
    dataptr[8 * 2] = tmp13 + z1;                              /* phase 5 */
    dataptr[8 * 6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5; /* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = (tmp10 - tmp12) * ((float) 0.382683433); /* c6 */
    z2 = ((float) 0.541196100) * tmp10 + z5;      /* c2-c6 */
    z4 = ((float) 1.306562965) * tmp12 + z5;      /* c2+c6 */
    z3 = tmp11 * ((float) 0.707106781);           /* c4 */

    z11 = tmp7 + z3; /* phase 5 */
    z13 = tmp7 - z3;

    dataptr[8 * 5] = z13 + z2; /* phase 6 */
    dataptr[8 * 3] = z13 - z2;
    dataptr[8 * 1] = z11 + z4;
    dataptr[8 * 7] = z11 - z4;

    dataptr++; /* advance pointer to next column */
  }

  return true;
}
}   // namespace dlls::codecs::dct
