//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       vcorrect.cpp
\brief      Filter for correct image
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace uplifters { namespace vcorrect {

Filter::Filter () :
  soft_impl_ (std::make_shared<soft::Impl> ())
{
  finfo_.active_impl_ = soft_impl_;
  soft_impl_->update_property (finfo_.rprops_);
}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);
  UASSERT (!finfo_.active_impl_.expired ());
  finfo_.active_impl_.lock ()->update_property (finfo_.rprops_);
  return;
}


void
Filter::transform_int (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::transform_int: beg");
  prepare_transform (_info);

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      XULOG_TRACE ("Filter::transform_int: skip");
      return;
    }
  //  ���� ��������� � ������� � ������� (���������� ������� ����� � ������ �����) ���������� ��������� ��������� �����������.
  if (_info.pframe_events_)
    {
      XULOG_TRACE ("Filter::transform_int: _info.pframe_events_->size=" << _info.pframe_events_->size ());
      for (const auto& _event : *_info.pframe_events_)
        {
          auto _devent = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::interf::InterfCorrectImageEvent> (_event);
          if (_devent)
            {
              XULOG_TEST ("Filter::transform_int: update active corrector");
              finfo_.active_impl_ = _devent->is_active () ? _devent->get_interface () : soft_impl_;
              UASSERT (!finfo_.active_impl_.expired ());
              finfo_.active_impl_.lock ()->update_property (finfo_.rprops_);
            }
        }
    }

  IVideoBuff::raw_ptr _h16_buff = (*pbuff_)[utils::dbuffs::video::consts::offs::hue];
  IVideoBuff::raw_ptr _s16_buff = (*pbuff_)[utils::dbuffs::video::consts::offs::sat];
  IVideoBuff::raw_ptr _l16_buff = (*pbuff_)[utils::dbuffs::video::consts::offs::lit];

  auto _impl = finfo_.active_impl_.lock ();
  UASSERT (_impl);
  _impl->process (_h16_buff, _s16_buff, _l16_buff);
  XULOG_TRACE ("Filter::transform_int: end");
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

}}}      // namespace dlls::uplifters::vcorrect
