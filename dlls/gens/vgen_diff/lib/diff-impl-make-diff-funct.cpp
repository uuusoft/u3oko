//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       diff-impl-make-diff-funct.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_diff_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "diff-impl.hpp"

namespace dlls { namespace gens { namespace vgen_diff { namespace lib {

void
DiffImpl::make_diff_buff (const IVideoBuff& _src1, IVideoBuff& _src2res)
{
  ::libs::optim::io::MCallInfo _cinfo;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (const_cast<IVideoBuff::raw_ptr> (&_src1)));
  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (&_src2res));

  _cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;

  ::libs::optim::mcalls::InfoMFunct _tfunct (&abs_diff_);

  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}}      // namespace dlls::gens::vgen_diff::lib
