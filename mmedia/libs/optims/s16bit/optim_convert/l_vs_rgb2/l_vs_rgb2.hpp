#pragma once
/**
\file       l_vs_rgb.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_convert
*/

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
inline bool
check_rgb2l (::libs::optim::io::MCallInfo& info)
{
  if (1 != info.dsts_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (1 != info.srcs_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  const ::libs::optim::io::ProxyBuf& l   = info.dsts_[0];
  const ::libs::optim::io::ProxyBuf& rgb = info.srcs_[0];

  if (l.width_ != rgb.width_)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (l.height_ != rgb.height_)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  return true;
}


inline bool
check_l2rgb (::libs::optim::io::MCallInfo& info)
{
  if (1 != info.dsts_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (1 != info.srcs_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (1 != info.params_.pints_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  const ::libs::optim::io::ProxyBuf& l   = info.srcs_[0];
  const ::libs::optim::io::ProxyBuf& rgb = info.dsts_[0];

  if (l.width_ != rgb.width_)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (l.height_ != rgb.height_)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  return true;
}

/// Функция конвертирует YUY16->L
void yuy2_to_l_alu (::libs::optim::io::MCallInfo& info);
void l_to_yuy2_alu (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_alu (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_alu (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_sse1 (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_sse1 (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_sse2 (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_sse2 (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_avx1 (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_avx1 (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_avx2 (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_avx2 (::libs::optim::io::MCallInfo& info);

void rgb24_to_l_neon (::libs::optim::io::MCallInfo& info);
void l_to_rgb24_neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2
