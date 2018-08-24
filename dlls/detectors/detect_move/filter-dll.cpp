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

Filter::Filter ()
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);

  diff_impl_.init ();
  diff_impl_.set_props (&diff_props_);

  mops_impl_.init ();
  mops_impl_.set_props (&mops_props_);

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
  prepare_transform (_info);
  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      return;
    }

  diff_impl_.itransform (*pbuff_);
  mops_impl_.itransform (*pbuff_);
  itransform (_info);
  return;
}

}}}      // namespace dlls::detectors::detect_move
