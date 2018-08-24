//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       yuy2_y16_base.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "yuy2_y16.hpp"
#include "yuy2_y16_int.hpp"

namespace libs { namespace optim { namespace convert { namespace yuy2_y16 {

void
get_params (
  ::libs::optim::MCallInfo& _info,
  const ProxyBuff**         _yuy2,
  ProxyBuff**               _y16)
{
  CHECK_STATE (1 == _info.srcs_.size (), "failed, src not equal 1");
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dst not equal 1");

  *_yuy2 = &_info.srcs_[0];
  *_y16  = &_info.dsts_[0];

  CHECK_STATE (*_yuy2, "failed, empty yuy2");
  CHECK_STATE (_y16, "failed, empty y16");

  (*_yuy2)->check ();
  (*_y16)->check ();

  return;
}

}}}}      // namespace libs::optim::convert::yuy2_y16
