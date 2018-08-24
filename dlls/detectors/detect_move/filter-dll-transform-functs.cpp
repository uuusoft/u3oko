//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_detect_move
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace detectors { namespace detect_move {

void
Filter::itransform (TransformInfo& _info)
{
  IVideoBuff::raw_ptr _psrc = (*pbuff_)[finfo_.rprops_->buff_.indx_sbuff_];

  if (!_psrc)
    {
      return;
    }

  MCallInfo        _cinfo;
  std::vector<int> _counters (pthreads_->get_count_threads (), 0);
  const short      _bound = finfo_.rprops_->bound_;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_psrc));
  _cinfo.params_.evals_.push_back (boost::any_cast<std::vector<int>*> (&_counters));
  _cinfo.params_.evals_.push_back (boost::any_cast<short> (_bound));

  InfoMFunct _tfunct;
  _tfunct.pfunct_ = &count_if_ge_;

  pthreads_->mcall (_tfunct, _cinfo);

  int _sum_vals = 0;
  for (auto& _val : _counters)
    {
      _sum_vals += _val;
    }

  if (0 == _sum_vals)
    {
      return;
    }

  //DATA_LOG( "send detect event" );
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents_events::events::WrapperEventsEvent> (_rmsg);
  IEvent::ptr _irmsg;
  auto        _idmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::video::DetectViolation> (_irmsg);
  _dmsg->set_msg (_irmsg);
  _info.pframe_events_->push_back (_rmsg);
  return;
}

}}}      // namespace dlls::detectors::detect_move
