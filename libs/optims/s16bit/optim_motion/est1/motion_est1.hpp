#pragma once
/**
\file       motion_est1.hpp
\date       28.08.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_motion
\brief      Оцена движения
*/
#include "vals.hpp"

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {
//  syn
typedef ::libs::ievents::props::videos::generics::motion_est::BuffEventInfo BuffEventInfo;
/**
  \brief  empty brief
  */
void get_params (
  ::libs::optim::MCallInfo& _info,
  const io::ProxyBuff**     _cur_src,
  const io::ProxyBuff**     _prev_src,
  io::ProxyBuff**           _dst_vecs,
  const BuffEventInfo**     _ppparams);
/**
  \brief  empty brief
  */
void alu (::libs::optim::MCallInfo& _info);
void sse2 (::libs::optim::MCallInfo& _info);
void avx1 (::libs::optim::MCallInfo& _info);
void avx2 (::libs::optim::MCallInfo& _info);
void neon (::libs::optim::MCallInfo& _info);

}}}}}      // namespace libs::optim::s16bit::motion::est1
