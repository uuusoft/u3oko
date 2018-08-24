//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       vgen_mops.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2017
\copyright  www.uuusoft.com
\project    uuu_vgen_mops
\brief      Реализация фильтра МО.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls { namespace gens { namespace vgen_mops {

Filter::Filter ()
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);
  impl_.init ();
  impl_.set_props (finfo_.rprops_);
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

  impl_.itransform (*pbuff_);
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

}}}      // namespace dlls::gens::vgen_mops
