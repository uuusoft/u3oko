//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       impl-graduent-funct.cpp
\brief      Filter for correct image
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "impl.hpp"

namespace dlls { namespace uplifters { namespace vcorrect { namespace soft {

void
Impl::graduent_correct (IVideoBuff& _buff, const std::array<short, 256>& _vals2vals)
{
  MCallInfo _cinfo;

  _cinfo.dsts_.push_back (ProxyBuff (&_buff));
  _cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  _cinfo.params_.consts_.push_back (&_vals2vals[0]);
  _cinfo.params_.ints_.push_back (_vals2vals.size ());

  ::libs::optim::mcalls::InfoMFunct _tfunct (&grad_funct_);
  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}}      // namespace dlls::uplifters::vcorrect::soft
