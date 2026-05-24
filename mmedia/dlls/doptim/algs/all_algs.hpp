#pragma once
/**
\file       all_algs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_doptim_dll
*/
#include "mmedia/libs/optims/optims.hpp"

#include "../ioptim-alg.hpp"
#include "../ioptim-impl.hpp"

#include "rgb2hsl.hpp"
#include "rgb2l.hpp"
#include "rgb2l2.hpp"

#include "hsl2rgb.hpp"
#include "l2rgb.hpp"

#include "yuy22rgb.hpp"
#include "yuy22y16.hpp"

#include "uyvy2rgb.hpp"
#include "uyvy2y16.hpp"

#include "ycb2rgb24.hpp"
#include "nv212rgb.hpp"
#include "nv212y16.hpp"

#include "scale_flow_wany_nearest.hpp"
#include "scale_fixed_wdown_b2x2.hpp"

#include "set_const.hpp"
#include "add_const.hpp"
#include "cmp_gt_const.hpp"
#include "mul_rshift.hpp"

#include "sat2byte.hpp"
#include "graduent1.hpp"
#include "abs_diff.hpp"

#include "histogram.hpp"
#include "count_if_ge_alg.hpp"

#include "conv_mod_3x3.hpp"
#include "conv_mod_5x5.hpp"
#include "conv_mod_7x7.hpp"
#include "conv_mod_9x9.hpp"
#include "conv_mod_11x11.hpp"
#include "conv_mod_cond_3x3.hpp"

#include "remove_add_noise2.hpp"
#include "remove_add_noise3.hpp"

#include "average2x2.hpp"

#include "flip_y.hpp"

#include "motion_est1.hpp"

#include "vec2image1.hpp"

#include "freq_dct_b8x8_forward.hpp"
#include "freq_dct_b8x8_backward.hpp"

#include "x16_x8_alg.hpp"
#include "x8_x16_alg.hpp"

#include "i420_to_rgb24.hpp"
#include "i420_to_y16.hpp"

#include "rgb32_rgb24_alg.hpp"
