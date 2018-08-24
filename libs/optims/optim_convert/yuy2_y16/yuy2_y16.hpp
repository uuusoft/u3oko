#pragma once
/**
\file       yuy2_y16.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace convert { namespace yuy2_y16 {
/**
  \brief  empty brief
  */
void get_params (::libs::optim::MCallInfo& _info, const ProxyBuff** _yuy2, ProxyBuff** _y16);

void alu (::libs::optim::MCallInfo& _info);
void sse2 (::libs::optim::MCallInfo& _info);
void avx2 (::libs::optim::MCallInfo& _info);
void neon (::libs::optim::MCallInfo& _info);

}}}}      // namespace libs::optim::convert::yuy2_y16
