//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mops-impl-binary-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief      Реализация впомогательной функции бинаризации изображения. Не является МО, но требуется для
            реализации МО через свертку.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"

namespace dlls { namespace gens { namespace vgen_mops { namespace lib {

void
MopsImpl::bin_buff (
  const off_buff2info_type& _b2b,
  const short               _bound,
  const short               _val,
  IVideoBuff*               _pdst)
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

}}}}      // namespace dlls::gens::vgen_mops::lib
