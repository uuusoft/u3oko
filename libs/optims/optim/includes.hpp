#pragma once
/**
\file       includes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      Внешний интерфейс включения модуля.
*/

#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes.hpp"


#include "mmedia/libs/optims/s16bit/optim_scale/flow/wany/nearest/scale_nearest.hpp"
#include "mmedia/libs/optims/s16bit/optim_scale/fixed/wdown/b2x2/scale_wdown_b2x2.hpp"


#include "mmedia/libs/optims/s16bit/optim_ops/add_sub_mul_neg_abs.hpp"
#include "mmedia/libs/optims/s16bit/optim_ops/const_add_sub_mul_neg_abs.hpp"


#include "mmedia/libs/optims/s16bit/optim_convert/hsl_vs_rgb/hsl_vs_rgb.hpp"
#include "mmedia/libs/optims/s16bit/optim_convert/l_vs_rgb/l_vs_rgb.hpp"
#include "mmedia/libs/optims/s16bit/optim_convert/l_vs_rgb2/l_vs_rgb2.hpp"


#include "mmedia/libs/optims/s16bit/optim_gen/gradient1/gradient1.hpp"
#include "mmedia/libs/optims/s16bit/optim_gen/matrix1/matrix1.hpp"
#include "mmedia/libs/optims/s16bit/optim_gen/create_image1/create_image_y1.hpp"
#include "mmedia/libs/optims/s16bit/optim_gen/graduent1/graduent1.hpp"
#include "mmedia/libs/optims/s16bit/optim_gen/vec2image1/vec2image1.hpp"


#include "mmedia/libs/optims/s16bit/optim_statistics/histogram/histogram1.hpp"
#include "mmedia/libs/optims/s16bit/optim_statistics/count_if_ge/count_if_ge.hpp"


#include "mmedia/libs/optims/s16bit/optim_bits/two_source/set/bits_two_source_set_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/two_source/or/bits_two_source_or_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/two_source/and/bits_two_source_and_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/two_source/andn/bits_two_source_andn_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/two_source/xor/bits_two_source_xor_ops.hpp"


#include "mmedia/libs/optims/s16bit/optim_bits/one_source/set/bits_one_source_set_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/one_source/or/bits_one_source_or_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/one_source/and/bits_one_source_and_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/one_source/andn/bits_one_source_andn_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/one_source/shr/bits_one_source_shr_ops.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/one_source/xor/bits_one_source_xor_ops.hpp"


#include "mmedia/libs/optims/s16bit/optim_bits/cmp/gt_add/gt_add.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/cmp/gt_mull_rshift_add/gt_mull_rshift_add.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/cmp/gt_const1_mull_add/gt_const1_mull_add.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/cmp/gt_add_const/gt_add_const.hpp"
#include "mmedia/libs/optims/s16bit/optim_bits/cmp/gt_const/gt_const.hpp"


#include "mmedia/libs/optims/s16bit/optim_bits/key_source/key_source.hpp"


#include "mmedia/libs/optims/s16bit/optim_filter/median1/median1.hpp"


#include "mmedia/libs/optims/s16bit/optim_filter/noise/var1/noise_remover1_x86.hpp"
#include "mmedia/libs/optims/s16bit/optim_filter/noise/var2/noise_remover2_x86.hpp"
#include "mmedia/libs/optims/s16bit/optim_filter/noise/var3/noise_remover3_x86.hpp"


#include "mmedia/libs/optims/s16bit/optim_conv/cond_convolution_3x3.hpp"


#include "mmedia/libs/optims/s16bit/optim_conv/base/c3x3/base_3x3.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/base/c5x5/base_5x5.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/base/c7x7/base_7x7.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/base/c9x9/base_9x9.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/base/c11x11/base_11x11.hpp"


#include "mmedia/libs/optims/s16bit/optim_block/flip_y/flip_y.hpp"


#include "mmedia/libs/optims/s16bit/optim_motion/est1/motion_est1.hpp"


#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/forward/freq_dct_b8x8_forward.hpp"
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/backward/freq_dct_b8x8_backward.hpp"


#include "mmedia/libs/optims/optim/io/includes.hpp"
