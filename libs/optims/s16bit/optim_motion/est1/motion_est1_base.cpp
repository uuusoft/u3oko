//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file     motion_est1_base.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date     28.08.2016
\project  uuu_optim_motion
\brief    Оценка движения в кадре.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {

void
get_params (
  ::libs::optim::MCallInfo& _info,
  const io::ProxyBuff**     _cur_src,
  const io::ProxyBuff**     _prev_src,
  io::ProxyBuff**           _dst_vecs,
  const BuffEventInfo**     _ppparams)
{
  CHECK_STATE (1 == _info.params_.evals_.size (), "failed, invald evals");
  CHECK_STATE (2 == _info.srcs_.size (), "failed, src not equal 2");
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dsts not equal 1");

  *_cur_src  = &_info.srcs_[0];
  *_prev_src = &_info.srcs_[1];
  *_dst_vecs = &_info.dsts_[0];

  CHECK_STATE (*_cur_src, "failed, empty cur_src");
  CHECK_STATE (*_prev_src, "failed, empty prev_src");
  CHECK_STATE (*_dst_vecs, "failed, empty dst_vecs");

  *_ppparams = boost::any_cast<const BuffEventInfo*> (_info.params_.evals_[0]);

  CHECK_STATE (*_ppparams, "failed, emty params");

  (**_ppparams).check ();

  CHECK_STATE (!(**_ppparams).search_vecs_.empty (), "failed, empty search vecs");
  return;
}

}}}}}      // namespace libs::optim::s16bit::motion::est1
