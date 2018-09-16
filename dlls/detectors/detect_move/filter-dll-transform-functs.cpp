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
  IVideoBuff::raw_ptr _psrc = (*pbuff_)[finfo_.rprops_->buffs_.indx_sbuff_];
  IVideoBuff::raw_ptr _pdst = (*pbuff_)[finfo_.rprops_->buffs_.indx_dbuff_];
  UASSERT (_psrc);
  UASSERT (_pdst);

  diff_impl_.itransform (*pbuff_);

  for (int _indx_mop = 0; _indx_mop < finfo_.rprops_->counter_morph_op_; ++_indx_mop)
    {
      mops_impl_.itransform (*pbuff_);
    }

  if (!_pdst || _pdst->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_WARNING ("empty diff dst buffer");
      return;
    }

  MCallInfo        _cinfo;
  std::vector<int> _counters (pthreads_->get_count_threads (), 0);
  const short      _bound = 1;      //finfo_.rprops_->bound_;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_pdst));
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

  IEvent::ptr _rmsg;

  if (_sum_vals)
    {
      if (0 == count_detects_)
        {
          time_first_detect_ = boost::posix_time::microsec_clock::universal_time ();
          XULOG_TRACE ("send detect event, sum_vals=" << _sum_vals);
          auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents_events::events::AddEvent2Base> (_rmsg);
          IEvent::ptr _irmsg;
          auto        _idmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::video::DetectViolation> (_irmsg);
          _dmsg->set_event (_irmsg);
          _idmsg->set_state (::libs::ievents::runtime::video::StateDetectViolation::start);
        }
      ++count_detects_;
    }
  else
    {
      if (count_detects_)
        {
          const auto _now_time = boost::posix_time::microsec_clock::universal_time ();
          if (_now_time - time_first_detect_ >= boost::posix_time::seconds (finfo_.rprops_->time_after_last_move_))
            {
              count_detects_ = 0;

              auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents_events::events::AddEvent2Base> (_rmsg);
              IEvent::ptr _irmsg;
              auto        _idmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::video::DetectViolation> (_irmsg);
              _dmsg->set_event (_irmsg);
              _idmsg->set_state (::libs::ievents::runtime::video::StateDetectViolation::stop);
            }
        }
    }

  if (_rmsg)
    {
      _info.pframe_events_->push_back (_rmsg);
    }
  return;
}

}}}      // namespace dlls::detectors::detect_move
