//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ioptim-impl-construct-funct.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "ioptim-alg.hpp"
#include "ioptim-impl.hpp"
#include "algs/all_algs_impl.hpp"

#ifndef ADD_ALG2AP
#define ADD_ALG2AP(MTYPE)                                                          \
  {                                                                                \
    const std::string& _key = MTYPE::val_key;                                      \
    UASSERT (algs_.end () == algs_.find (_key));                                   \
    algs_.insert (str2functs_type::value_type (_key, std::make_shared<MTYPE> ())); \
  }
#endif

namespace dlls { namespace doptim { namespace impl {

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
  ADD_ALG2AP (algs::YCB2RgbAlg);
  ADD_ALG2AP (algs::CYUY22Y16Alg);
  ADD_ALG2AP (algs::CNV212RgbAlg);
  ADD_ALG2AP (algs::CNV212Y16Alg);
  ADD_ALG2AP (algs::CFreqDCT8x8ForwardAlg);
  ADD_ALG2AP (algs::CFreqDCT8x8BackwardAlg);
  ADD_ALG2AP (algs::CCountIfGEAlg);
  ADD_ALG2AP (algs::CX16_X8Alg);
  ADD_ALG2AP (algs::CX8_X16Alg);
  return;
}

}}}      // namespace dlls::doptim::impl
