/**
\file       ioptim-impl-construct-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_doptim_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "doptim-includes_int.hpp"
#include "ioptim-alg.hpp"
#include "ioptim-impl.hpp"
#include "algs/all_algs_impl.hpp"

#ifndef ADD_ALG2AP
#  define ADD_ALG2AP(MTYPE)                                                          \
    {                                                                                \
      const std::string& key = MTYPE::val_key;                                       \
      U3_ASSERT (algs_.end () == algs_.find (key));                                  \
      algs_.insert (str2funcs_type::value_type (key, std::make_shared< MTYPE > ())); \
    }
#endif

namespace dlls::doptim::impl
{
void
IOptimImpl::construct ()
{
  algs_.clear ();

  ADD_ALG2AP (algs::CRgb2HSLAlg);
  ADD_ALG2AP (algs::CRgb2LAlg);
  ADD_ALG2AP (algs::CRgb2LAlg2);
  ADD_ALG2AP (algs::CSetConstAlg);
  ADD_ALG2AP (algs::CScaleNearestAlg);
  ADD_ALG2AP (algs::CScaleFixedDown2x2Alg);
  ADD_ALG2AP (algs::CAddConstAlg);
  ADD_ALG2AP (algs::CGraduent1Alg);
  ADD_ALG2AP (algs::CSat2ByteAlg);
  ADD_ALG2AP (algs::CCmpGTConstAlg);
  ADD_ALG2AP (algs::CAbsDiffAlg);
  ADD_ALG2AP (algs::CConvMod3x3Alg);
  ADD_ALG2AP (algs::CConvMod5x5Alg);
  ADD_ALG2AP (algs::CConvMod7x7Alg);
  ADD_ALG2AP (algs::CConvMod9x9Alg);
  ADD_ALG2AP (algs::CConvMod11x11Alg);
  ADD_ALG2AP (algs::CRemoveAddNoise2Alg);
  ADD_ALG2AP (algs::CRemoveAddNoise3Alg);
  ADD_ALG2AP (algs::CHistogramAlg);
  ADD_ALG2AP (algs::CConvModCond3x3Alg);
  ADD_ALG2AP (algs::CFlipYAlg);
  ADD_ALG2AP (algs::CMotionEst1Alg);
  ADD_ALG2AP (algs::CVec2Image1Alg);
  ADD_ALG2AP (algs::CHSL2RgbAlg);
  ADD_ALG2AP (algs::CL2RgbAlg);
  ADD_ALG2AP (algs::CYUY22RgbAlg);
  ADD_ALG2AP (algs::CYUY22Y16Alg);
  ADD_ALG2AP (algs::CUYVY2RgbAlg);
  ADD_ALG2AP (algs::CUYVY2Y16Alg);
  ADD_ALG2AP (algs::YCB2RgbAlg);
  ADD_ALG2AP (algs::CNV212RgbAlg);
  ADD_ALG2AP (algs::CNV212Y16Alg);
  ADD_ALG2AP (algs::CFreqDCT8x8ForwardAlg);
  ADD_ALG2AP (algs::CFreqDCT8x8BackwardAlg);
  ADD_ALG2AP (algs::CCountIfGEAlg);
  ADD_ALG2AP (algs::CX16_X8Alg);
  ADD_ALG2AP (algs::CX8_X16Alg);
  ADD_ALG2AP (algs::I420ToRgb24Alg);
  ADD_ALG2AP (algs::CRGB32_RGB24Alg);
}
}   // namespace dlls::doptim::impl
