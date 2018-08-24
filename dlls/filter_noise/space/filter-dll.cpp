//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\date       26.07.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Файл реализации фильтрации в пространственной области.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace filter_noise { namespace space {

Filter::Filter ()
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);
  update_impl ();
  impl_->load_int ();
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
Filter::update_impl ()
{
  const auto& _name = finfo_.rprops_->name_impl_;
  XULOG_TRACE ("Filter::update_impl::select impl by string, " << _name);
  if ("rang" == _name)
    {
      impl_.reset (new impl::rang::RangFilter);
      return;
    }
  XULOG_WARNING ("unknown type filter impl, " << _name);
  impl_.reset (new impl::rang::RangFilter);
  return;
}

}}}      // namespace dlls::filter_noise::space
