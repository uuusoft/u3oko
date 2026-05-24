#pragma once
/**
\brief  ???
\file optim.hpp
*/

#include "optim/calls/CCaller.hpp"


#include "optim/s16bit/optim_s16bit.hpp"


#include "optim/s16bit/scale/any_array/nearest/scale_nearest.hpp"


#include "optim/s16bit/ops/add_sub_mul_neg_abs.hpp"
#include "optim/s16bit/ops/const_add_sub_mul_neg_abs.hpp"


#include "optim/s16bit/convert/hsl_vs_rgb/hsl_vs_rgb.hpp"
#include "optim/s16bit/convert/l_vs_rgb/l_vs_rgb.hpp"


#include "optim/s16bit/gen/gradient1/gradient1.hpp"
#include "optim/s16bit/gen/matrix1/matrix1.hpp"
#include "optim/s16bit/gen/create_image1/create_image_y1.hpp"


#include "optim/s16bit/bits/two_source/set/bits_two_source_set_ops.hpp"
#include "optim/s16bit/bits/two_source/or/bits_two_source_or_ops.hpp"
#include "optim/s16bit/bits/two_source/and/bits_two_source_and_ops.hpp"
#include "optim/s16bit/bits/two_source/andn/bits_two_source_andn_ops.hpp"
#include "optim/s16bit/bits/two_source/xor/bits_two_source_xor_ops.hpp"


#include "optim/s16bit/bits/one_source/set/bits_one_source_set_ops.hpp"
#include "optim/s16bit/bits/one_source/or/bits_one_source_or_ops.hpp"
#include "optim/s16bit/bits/one_source/and/bits_one_source_and_ops.hpp"
#include "optim/s16bit/bits/one_source/andn/bits_one_source_andn_ops.hpp"
#include "optim/s16bit/bits/one_source/shr/bits_one_source_shr_ops.hpp"
#include "optim/s16bit/bits/one_source/xor/bits_one_source_xor_ops.hpp"


#include "optim/s16bit/bits/cmp/gt_add/gt_add.hpp"
#include "optim/s16bit/bits/cmp/gt_mull_rshift_add/gt_mull_rshift_add.hpp"
#include "optim/s16bit/bits/cmp/gt_const1_mull_add/gt_const1_mull_add.hpp"
#include "optim/s16bit/bits/cmp/gt_add_const/gt_add_const.hpp"
#include "optim/s16bit/bits/cmp/gt_const/gt_const.hpp"


#include "optim/s16bit/bits/key_source/key_source.hpp"


#include "optim/s16bit/gen/histogram/histogram1.hpp"
#include "optim/s16bit/gen/graduent1/graduent1.hpp"


#include "optim/s16bit/filter/aver_2x2_8x8.hpp"
#include "optim/s16bit/filter/median1/median1.hpp"


#include "optim/s16bit/filter/noise/var1/noise_remover1_x86.hpp"
#include "optim/s16bit/filter/noise/var2/noise_remover2_x86.hpp"
#include "optim/s16bit/filter/noise/var3/noise_remover3_x86.hpp"


#include "optim/s16bit/convolution/cond_convolution_3x3.hpp"


#include "optim/s16bit/convolution/base/c3x3/base_3x3.hpp"
#include "optim/s16bit/convolution/base/c5x5/base_5x5.hpp"
#include "optim/s16bit/convolution/base/c7x7/base_7x7.hpp"
#include "optim/s16bit/convolution/base/c9x9/base_9x9.hpp"
#include "optim/s16bit/convolution/base/c11x11/base_11x11.hpp"


#include "optim/s16bit/block/flip_y/flip_y.hpp"


#include "optim/s16bit/motion/est1/motion_est1.hpp"


#include "optim/s16bit/gen/vec2image1/vec2image1.hpp"


#include "optim/s16bit/freq/dct/b8x8/forward/freq_dct_b8x8_forward.hpp"
#include "optim/s16bit/freq/dct/b8x8/backward/freq_dct_b8x8_backward.hpp"


#include "optim/io/ioptim.hpp"
#include "optim/io/ioptim_proxy.hpp"
