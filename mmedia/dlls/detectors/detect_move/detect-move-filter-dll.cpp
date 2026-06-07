/**
\file       detect-move-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_move
*/
#include "detect-move-includes_int.hpp"
#include "detect-move-info-filter-dll.hpp"
#include "detect-move-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::detectors::detect_move
{
void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim  = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();
  count_if_ge_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCountIfGEAlg::val_key));
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  syn::IVideoBuf::raw_ptr psrc = (*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_];
  if (!psrc || psrc->get_flag (::utils::dbufs::BufFlags::empty))
  {
    return;
  }

  itransform (info);
}


std::int32_t
Filter::get_move_count (syn::IVideoBuf::raw_ptr pdst)
{
  ::libs::optim::io::MCallInfo cinfo;
  std::vector< int >           counters (pthreads_->get_count_threads (), 0);
  const std::int16_t           bound    = 1;   // finfo_.rprops_->bound_;
  std::int32_t                 sum_vals = 0;

  cinfo.srcs_.emplace_back (pdst, "pdst dlls::detectors::detect_move");
  cinfo.params_.evals_.emplace_back (boost::any_cast< std::vector< int >* > (&counters));
  cinfo.params_.evals_.emplace_back (boost::any_cast< std::int16_t > (bound));

  ::libs::optim::mcalls::MTFuncInfo tfunc;
  tfunc.pfunc_           = &count_if_ge_;
  tfunc.src_align_.px_y_ = 1;
  tfunc.dst_align_.px_y_ = 1;

  pthreads_->mthreads_call (
    id_obj_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);

  for (auto& val : counters)
  {
    sum_vals += val;
  }
  return sum_vals;
}


void
Filter::itransform (syn::TransformInfo& info)
{
  syn::IVideoBuf::raw_ptr pdst = (*pbuf_)[finfo_.rprops_->bufs_.indx_dbuf_];

  finfo_.diff_impl_.set_transform_info (transinfo_);
  finfo_.diff_impl_.itransform (id_obj_, *pbuf_);
  finfo_.diff_impl_.set_transform_info (nullptr);

  for (std::int32_t indx_mop = 0; indx_mop < finfo_.rprops_->counter_morph_op_; ++indx_mop)
  {
    finfo_.mops_impl_.set_transform_info (transinfo_);
    finfo_.mops_impl_.itransform (id_obj_, *pbuf_);
    finfo_.mops_impl_.set_transform_info (nullptr);
  }

  if (!pdst || pdst->get_flag (::utils::dbufs::BufFlags::empty))
  {
    U3_LOG_DATA_WRN ("empty diff dst buf" + TOLOG (finfo_.rprops_->bufs_.indx_dbuf_));
    return;
  }

  const auto       sum_vals = get_move_count (pdst);
  syn::IEvent::ptr rmsg;

  if (sum_vals)
  {
    if (0 == count_detects_)
    {
      U3_LOG_DATA_DEV ("signal video detect start" + VTOLOG (sum_vals));
      time_first_detect_ = boost::posix_time::microsec_clock::universal_time ();

      syn::IEvent::ptr irmsg;
      auto             dmsg  = ::libs::iproperties::helpers::create_event< syn::AddEvent2Base > (rmsg, libs::helpers::utils::cuuid (), "???????");
      auto             idmsg = ::libs::iproperties::helpers::create_event< syn::DetectViolation > (irmsg, ::libs::ievents::runtime::video::DetectViolations::start);
      dmsg->set_event (irmsg);
      // idmsg->set_state (::libs::ievents::runtime::video::DetectViolations::start);
    }
    ++count_detects_;
  }
  else
  {
    if (count_detects_)
    {
      const auto now_time = boost::posix_time::microsec_clock::universal_time ();
      if (now_time - time_first_detect_ >= boost::posix_time::seconds (finfo_.rprops_->time_after_last_move_))
      {
        U3_LOG_DATA_DEV ("signal video detect stop");
        count_detects_ = 0;

        syn::IEvent::ptr irmsg;
        auto             dmsg  = ::libs::iproperties::helpers::create_event< syn::AddEvent2Base > (rmsg, libs::helpers::utils::cuuid (), "???????");
        auto             idmsg = ::libs::iproperties::helpers::create_event< syn::DetectViolation > (irmsg, ::libs::ievents::runtime::video::DetectViolations::stop);
        dmsg->set_event (irmsg);
        // idmsg->set_state (::libs::ievents::runtime::video::DetectViolations::stop);
      }
    }
  }

  if (rmsg)
  {
    info.frame_events_->push_back (rmsg);
  }
}
}   // namespace dlls::detectors::detect_move
