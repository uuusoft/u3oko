//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       diff-impl-bin-buff-funct.cpp
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
DiffImpl::bin_buff (const short _bound, const short _val, IVideoBuff* _pdst)
{
  ::libs::optim::io::MCallInfo _cinfo;

  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_pdst));

  _cinfo.params_.evals_.push_back (boost::any (::libs::optim::s16bit::consts::us_all_xffff));
  _cinfo.params_.evals_.push_back (boost::any (_bound));
  _cinfo.params_.evals_.push_back (boost::any (_val));

  ::libs::optim::mcalls::InfoMFunct _tfunct (&cmp_get_const_);

  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}}      // namespace dlls::gens::vgen_diff::lib
