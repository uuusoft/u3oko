/**
\file       ioptim-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_doptim_dll
*/
#include "doptim-includes_int.hpp"
#include "ioptim-alg.hpp"
#include "ioptim-impl.hpp"
#include "algs/all_algs.hpp"

namespace dlls::doptim::impl
{
IOptimImpl::IOptimImpl ()
{
  lock_type lock (mtx_);
  construct ();
}


syn::hioptim
IOptimImpl::get (const ::libs::optim::io::qoptim& query)
{
  lock_type lock (mtx_);
  auto      find = algs_.find (query.id_);

  if (algs_.end () == find)
  {
    U3_ASSERT (query.id_.c_str () && 0);
    return syn::hioptim (nullptr);
  }

  U3_ASSERT (find->second);
  syn::hioptim ret = find->second->get ();
  U3_ASSERT (ret.self_test ());
  return ret;
}


void
IOptimImpl::sync_impl (const ::libs::optim::io::TInit& iinfo)
{
  ::libs::helpers::sys::cpu::TextExtCpu cpu_helper;
  lock_type                             lock (mtx_);
  for (str2funcs_type::value_type& val : algs_)
  {
    U3_ASSERT (val.second);
    val.second->sync_impl (iinfo);
  }
}


void
IOptimImpl::construct ()
{
  U3_ASSERT (algs_.empty ());

  add_alg< algs::CRgb2HSLAlg > ();
  add_alg< algs::CRgb2LAlg > ();
  add_alg< algs::CRgb2LAlg2 > ();
  add_alg< algs::CSetConstAlg > ();
  add_alg< algs::CScaleNearestAlg > ();
  add_alg< algs::CScaleFixedDown2x2Alg > ();
  add_alg< algs::CAddConstAlg > ();
  add_alg< algs::CGraduent1Alg > ();
  add_alg< algs::CSat2ByteAlg > ();
  add_alg< algs::CCmpGTConstAlg > ();
  add_alg< algs::CAbsDiffAlg > ();
  add_alg< algs::CConvMod3x3Alg > ();
  add_alg< algs::CConvMod5x5Alg > ();
  add_alg< algs::CConvMod7x7Alg > ();
  add_alg< algs::CConvMod9x9Alg > ();
  add_alg< algs::CConvMod11x11Alg > ();
  add_alg< algs::CRemoveAddNoise2Alg > ();
  add_alg< algs::CRemoveAddNoise3Alg > ();
  add_alg< algs::CHistogramAlg > ();
  add_alg< algs::CConvModCond3x3Alg > ();
  add_alg< algs::CFlipYAlg > ();
  add_alg< algs::CMotionEst1Alg > ();
  add_alg< algs::CVec2Image1Alg > ();
  add_alg< algs::CHSL2RgbAlg > ();
  add_alg< algs::CL2RgbAlg > ();
  add_alg< algs::CYUY22RgbAlg > ();
  add_alg< algs::CYUY22Y16Alg > ();
  add_alg< algs::CUYVY2RgbAlg > ();
  add_alg< algs::CUYVY2Y16Alg > ();
  add_alg< algs::YCB2RgbAlg > ();
  add_alg< algs::CNV212RgbAlg > ();
  add_alg< algs::CNV212Y16Alg > ();
  add_alg< algs::CFreqDCT8x8ForwardAlg > ();
  add_alg< algs::CFreqDCT8x8BackwardAlg > ();
  add_alg< algs::CCountIfGEAlg > ();
  add_alg< algs::CX16_X8Alg > ();
  add_alg< algs::CX8_X16Alg > ();
  add_alg< algs::I420ToRgb24Alg > ();
  add_alg< algs::CRGB32_RGB24Alg > ();
}
}   // namespace dlls::doptim::impl
