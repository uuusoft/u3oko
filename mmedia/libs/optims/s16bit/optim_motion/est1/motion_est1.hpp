#pragma once
/**
\file       motion_est1.hpp
\date       28.08.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_motion
\brief      Оцена движения
*/
#include "vals.hpp"

namespace libs::optim::s16bit::motion::est1
{
using EventBufsInfoMotionEst = ::libs::ievents::props::videos::generic::motion_est::EventBufsInfoMotionEst;

void get_params (
  ::libs::optim::io::MCallInfo& info,
  const io::ProxyBuf**          cur_src,
  const io::ProxyBuf**          prev_src,
  io::ProxyBuf**                dst_vecs,
  EventBufsInfoMotionEst**      ppparams);

void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::motion::est1
