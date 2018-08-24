#pragma once
/**
\file       l_vs_rgb.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb {
/**
  \brief  empty brief
  */
inline bool
check_rgb2l (::libs::optim::MCallInfo& _info)
{
  if (1 != _info.dsts_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (1 != _info.srcs_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  const ::libs::optim::io::ProxyBuff& _l   = _info.dsts_[0];
  const ::libs::optim::io::ProxyBuff& _rgb = _info.srcs_[0];

  if (_l.width_ != _rgb.width_)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (_l.height_ != _rgb.height_)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  return true;
}
/**
  \brief  empty brief
  */
inline bool
check_l2rgb (::libs::optim::MCallInfo& _info)
{
  if (1 != _info.dsts_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (1 != _info.srcs_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (1 != _info.params_.pints_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  const ::libs::optim::io::ProxyBuff& _l   = _info.srcs_[0];
  const ::libs::optim::io::ProxyBuff& _rgb = _info.dsts_[0];

  if (_l.width_ != _rgb.width_)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (_l.height_ != _rgb.height_)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  return true;
}
/**
  \brief  Функция конвертирует YUY16->L
  */
void yuy2_to_l_alu (::libs::optim::MCallInfo& _info);
void l_to_yuy2_alu (::libs::optim::MCallInfo& _info);

void rgb24_to_l_alu (::libs::optim::MCallInfo& _info);
void l_to_rgb24_alu (::libs::optim::MCallInfo& _info);

void rgb24_to_l_sse1 (::libs::optim::MCallInfo& _info);
void l_to_rgb24_sse1 (::libs::optim::MCallInfo& _info);

void rgb24_to_l_sse2 (::libs::optim::MCallInfo& _info);
void l_to_rgb24_sse2 (::libs::optim::MCallInfo& _info);

void rgb24_to_l_avx1 (::libs::optim::MCallInfo& _info);
void l_to_rgb24_avx1 (::libs::optim::MCallInfo& _info);

void rgb24_to_l_avx2 (::libs::optim::MCallInfo& _info);
void l_to_rgb24_avx2 (::libs::optim::MCallInfo& _info);

void rgb24_to_l_neon (::libs::optim::MCallInfo& _info);
void l_to_rgb24_neon (::libs::optim::MCallInfo& _info);

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb
