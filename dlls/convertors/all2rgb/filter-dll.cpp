//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_all2rgb
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace convertors { namespace all2rgb {

Filter::Filter ()
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);

  finfo_.load (_node);

  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  yuy2_to_rgb24_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CYUY22RgbAlg::val_key));
  yuy2_to_y16_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CYUY22Y16Alg::val_key));
  nv21_to_rgb24_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CNV212RgbAlg::val_key));
  nv21_to_y16_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CNV212Y16Alg::val_key));
  ycb_to_rgb24_  = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::YCB2RgbAlg::val_key));
  scale_funct_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CScaleNearestAlg::val_key));
  return;
}


void
Filter::transform_int (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::transform_int, beg");
  prepare_transform (_info);

  auto& _ibuff = (*_info.ibuff_);

  if (_ibuff->get_flag (::libs::buffs::TypeBuffsFlags::empty))
    {
      //  Пустой буфер допустим, например если все преобразование происходит аппаратно.
      XULOG_TRACE ("Filter::transform_int, skip, emtpy buffs");
      return;
    }

  auto _sbuff = (*_ibuff)[finfo_.rprops_->buff_.indx_sbuff_];
  auto _dbuff = (*_ibuff)[finfo_.rprops_->buff_.indx_dbuff_];

  if (!_sbuff || !_dbuff)
    {
      XULOG_TRACE ("skip transform yuy2->rgb, null buffs, " << finfo_.rprops_->buff_.indx_sbuff_ << ", " << finfo_.rprops_->buff_.indx_dbuff_);
      return;
    }

  if (_sbuff->get_flag (utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_TRACE ("skip transform yuy2->rgb, empty source buff, " << finfo_.rprops_->buff_.indx_sbuff_);
      return;
    }

  pbuff_->set_flag (::libs::buffs::TypeBuffsFlags::request_convert2hsl, true);

  //  allready
  if (::libs::helpers::uids::minor::rgb24 == _sbuff->get_format ())
    {
      XULOG_TRACE ("Filter::transform_int, skip, redy rgb24");
      return;
    }
  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      XULOG_TRACE ("Filter::transform_int, skip, disabled");
      return;
    }

  const auto _buff_format = _sbuff->get_format ();
  if (::libs::helpers::uids::minor::yuy2 != _buff_format && ::libs::helpers::uids::minor::nv21 != _buff_format && ::libs::helpers::uids::minor::ycb != _buff_format)
    {
      XULOG_WARNING ("only yuy2, ycb, nv21 formats accepted, not this " << ::libs::helpers::uids::helpers::get_readable_name (_buff_format));
      return;
    }

  itransform ();
  XULOG_TRACE ("Filter::transform_int, end");
  return;
}


::libs::optim::io::hioptim*
Filter::get_funct_for_format (const cuuid& _format)
{
  const bool _mono = finfo_.rprops_->strip_color_;

  if (::libs::helpers::uids::minor::yuy2 == _format)
    {
      return _mono ? &yuy2_to_y16_ : &yuy2_to_rgb24_;
    }
  if (::libs::helpers::uids::minor::ycb == _format)
    {
      return _mono ? &yuy2_to_y16_ : &ycb_to_rgb24_;
    }
  if (::libs::helpers::uids::minor::nv21 == _format)
    {
      return _mono ? &nv21_to_y16_ : &nv21_to_rgb24_;
    }
  XULOG_ERROR ("unknown pixel format, " << ::libs::helpers::uids::helpers::get_readable_name (_format));
  return nullptr;
}


cuuid
Filter::get_out_format_from_format (const cuuid& _format)
{
  const bool _mono = finfo_.rprops_->strip_color_;
  return _mono ? ::libs::helpers::uids::minor::y16 : ::libs::helpers::uids::minor::rgb24;
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

}}}      // namespace dlls::convertors::all2rgb
