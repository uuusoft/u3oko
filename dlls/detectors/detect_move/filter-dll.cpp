//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
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
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace detectors { namespace detect_move {

Filter::Filter () :
  count_detects_ (0),
  time_first_detect_ (boost::posix_time::microsec_clock::universal_time ())
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);

  {
    InfoBuffVideoDiffProp _detect_prop;

    _detect_prop.op_.enable_        = true;
    _detect_prop.op_.bound_filling_ = finfo_.rprops_->bound_;
    _detect_prop.op_.val_filling_   = 1;
    _detect_prop.bindx_diff_        = finfo_.rprops_->buffs_.indx_dbuff_;

    diff_props_.diffs_.push_back ({ finfo_.rprops_->buffs_.indx_sbuff_, _detect_prop });
    diff_impl_.init ();
    diff_impl_.set_props (&diff_props_);
  }

  {
    auto                 _morph_op = libs::ievents::props::videos::generic::morph::str2type_op (finfo_.rprops_->id_morph_op_);
    MorphOperationParams _morph_param (_morph_op, finfo_.rprops_->size_core_morph_op_, 0, 1);
    MorphBuffInfo        _morph_info (finfo_.rprops_->buffs_.indx_dbuff_, _morph_param);

    mops_props_.diffs_.push_back ({ finfo_.rprops_->buffs_.indx_dbuff_, _morph_info });
    mops_impl_.init ();
    mops_impl_.set_props (&mops_props_);
  }

  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();
  count_if_ge_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCountIfGEAlg::val_key));
  return;
}


void
Filter::call_int (CallInterfInfo& _info)
{
  super::prepare_call (_info);
  super::call_gen (_info);
  return;
}


void
Filter::init_pts (ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::PointFilter::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
  return;
}


void
Filter::transform_int (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::transform_int, beg");
  prepare_transform (_info);
  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      return;
    }

  IVideoBuff::raw_ptr _psrc = (*pbuff_)[finfo_.rprops_->buffs_.indx_sbuff_];
  if (!_psrc || _psrc->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      return;
    }

  itransform (_info);
  XULOG_TRACE ("Filter::transform_int, end");
  return;
}

}}}      // namespace dlls::detectors::detect_move
