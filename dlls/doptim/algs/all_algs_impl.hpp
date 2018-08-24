#pragma once
/**
\file       all_algs_impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/
#include "all_algs.hpp"
#if 0
namespace dlls { namespace doptim { namespace impl { namespace algs {

const std::string CAbsDiffAlg::val_key            = std::string ("libs.optim.s16bit.ops.sub_abs_diff");
const std::string CAddConstAlg::val_key           = std::string ("libs.optim.s16bit.ops.add_const");
const std::string CCmpGTConstAlg::val_key         = std::string ("libs.optim.s16bit.bits.cmp.gt_const");
const std::string CConvMod3x3Alg::val_key         = std::string ("libs.optim.s16bit.conv.base.mod_b3x3");
const std::string CConvMod5x5Alg::val_key         = std::string ("libs.optim.s16bit.conv.base.c5x5.mod");
const std::string CConvMod7x7Alg::val_key         = std::string ("libs.optim.s16bit.conv.base.c7x7.mod");
const std::string CConvMod9x9Alg::val_key         = std::string ("libs.optim.s16bit.conv.base.c9x9.mod");
const std::string CConvMod11x11Alg::val_key       = std::string ("libs.optim.s16bit.conv.base.c11x11.mod");
const std::string CConvModCond3x3Alg::val_key     = std::string ("libs.optim.s16bit.conv.mod_cond_b3x3");
const std::string CGraduent1Alg::val_key          = std::string ("libs.optim.s16bit.gen.graduent1");
const std::string CHistogramAlg::val_key          = std::string ("libs.optim.s16bit.statistics.histogram");
const std::string CCountIfGEAlg::val_key          = std::string ("libs.optim.s16bit.statistics.count_if_ge");
const std::string CHSL2RgbAlg::val_key            = std::string ("libs.optim.s16bit.convert.hsl_vs_rgb.hsl_to_rgb24");
const std::string CL2RgbAlg::val_key              = std::string ("libs.optim.s16bit.convert.l_vs_rgb.l_to_rgb24");
const std::string CMotionEst1Alg::val_key         = std::string ("libs.optim.s16bit.motion.est1");
const std::string CMulRShiftAlg::val_key          = std::string ("libs.optim.s16bit.ops.mul_rshift");
const std::string CNV212RgbAlg::val_key           = std::string ("libs.optim.convert.nv21_rgb24");
const std::string CNV212Y16Alg::val_key           = std::string ("libs.optim.convert.nv21_y16");
const std::string CRemoveAddNoise2Alg::val_key    = std::string ("libs.optim.s16bit.filter.noise.var2");
const std::string CRemoveAddNoise3Alg::val_key    = std::string ("libs.optim.s16bit.filter.noise.var3");
const std::string CRgb2HSLAlg::val_key            = std::string ("libs.optim.s16bit.convert.hsl_vs_rgb.rgb24_to_hsl");
const std::string CRgb2LAlg::val_key              = std::string ("libs.optim.s16bit.convert.l_vs_rgb.rgb24_to_l");
const std::string CRgb2LAlg2::val_key             = std::string ("libs.optim.s16bit.convert.l_vs_rgb2.rgb24_to_l");
const std::string CSat2ByteAlg::val_key           = std::string ("libs.optim.s16bit.ops.sat2byte");
const std::string CScaleNearestAlg::val_key       = std::string ("libs.optim.s16bit.scale.flow.wany.nearest");
const std::string CScaleFixedDown2x2Alg::val_key  = std::string ("libs.optim.s16bit.scale.fixed.wdown.b2x2");
const std::string CSetConstAlg::val_key           = std::string ("libs.optim.s16bit.bits.consts.set_const");
const std::string CVec2Image1Alg::val_key         = std::string ("libs.optim.s16bit.gen.vec2image1");
const std::string CFlipYAlg::val_key              = std::string ("libs.optim.s16bit.block.y_mirror");
const std::string CYUY22Y16Alg::val_key           = std::string ("libs.optim.convert.yuy2_y16");
const std::string CYUY22RgbAlg::val_key           = std::string ("libs.optim.convert.yuy2_rgb24");
const std::string CFreqDCT8x8ForwardAlg::val_key  = std::string ("libs.optim.s16bit.freq.dct.b8x8.forward");
const std::string CFreqDCT8x8BackwardAlg::val_key = std::string ("libs.optim.s16bit.freq.dct.b8x8.backward");
const std::string CX16_X8Alg::val_key             = std::string ("libs.optim.convert.x16_x8");
const std::string CX8_X16Alg::val_key             = std::string ("libs.optim.convert.x8_x16");

}}}}      // namespace dlls::doptim::impl::algs
#endif
