//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       yuy2_rgb24_base.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "yuy2_rgb24.hpp"
#include "yuy2_rgb24_int.hpp"

namespace libs { namespace optim { namespace convert { namespace yuy2_rgb24 {

void
get_params (
  ::libs::optim::MCallInfo& _info,
  const ProxyBuff**         _yuy2,
  ProxyBuff**               _rgb24)
{
  CHECK_STATE (1 == _info.srcs_.size (), "failed, src not equal 1");
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dsts not equal 1");

  *_yuy2  = &_info.srcs_[0];
  *_rgb24 = &_info.dsts_[0];

  CHECK_STATE (*_yuy2, "failed, tmpy yuy2");
  CHECK_STATE (_rgb24, "failed, empty rgb24");

  (*_yuy2)->check ();
  (*_rgb24)->check ();

  return;
}

}}}}      // namespace libs::optim::convert::yuy2_rgb24
