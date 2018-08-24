//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_all2hsl
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace convertors { namespace all2hsl {

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

  fx8_to_x16_          = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  rgb24_to_hsl_        = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2HSLAlg::val_key));
  rgb24_to_l_fast_     = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2LAlg::val_key));
  rgb24_to_l_accurate_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CRgb2LAlg2::val_key));
  set_const_funct_     = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CSetConstAlg::val_key));
  scale_funct_         = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CScaleNearestAlg::val_key));
  flip_y_              = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
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

  auto& _ibuffs = (*_info.ibuff_);

  if (_ibuffs->get_flag (::libs::buffs::TypeBuffsFlags::empty))
    {
      //  Пустой буфер допустим, например если все преобразование происходит аппаратно.
      return;
    }

  if (!_ibuffs->get_flag (::libs::buffs::TypeBuffsFlags::request_convert2hsl))
    {
      return;
    }

  auto        _indx_base_buff = ::utils::dbuffs::video::consts::offs::raw;
  auto        _base_buff      = (*_ibuffs)[_indx_base_buff];
  const auto& _format         = _base_buff->get_format ();

  if (_base_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      //  Требуется уточнение уже для непосредственного буфера источника. Пустой буфер допустим, например если все преобразование происходит аппаратно.
      return;
    }

  if (::libs::helpers::uids::minor::rgb24 != _format && ::libs::helpers::uids::minor::y16 != _format && ::libs::helpers::uids::minor::y8 != _format)
    {
      XULOG_WARNING ("unknow format for HSL convert, skip, indx=" << _indx_base_buff << ", format=" << ::libs::helpers::uids::helpers::get_readable_name (_format));
      return;
    }

  //  add offset for active data and corrected active data correct frame
  itransform ();
  pbuff_->set_flag (::libs::buffs::TypeBuffsFlags::request_convert2hsl, false);
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
Filter::alloc_fake_frame (TransformInfo& _info)
{
  (*_info.ibuff_)->reset (false);

  const short _bits_per_pixel = 24;
  const int   _req_width      = 320;
  const int   _req_height     = 240;
  const int   _req_stride     = ::libs::helpers::mem::get_align64 (_req_width * _bits_per_pixel / 8, true);
  const int   _req_size       = _req_stride * _req_height;
  auto        _base_buff      = (**_info.ibuff_)[(*_info.ibuff_)->get_indx_base_buff ()];

  //  for all other format create null frame RGB24 320x240
  _base_buff->set_dim_var (svideo::TypeDimVar::width, _req_width);
  _base_buff->set_dim_var (svideo::TypeDimVar::height, _req_height);

  IVideoBuff::raw_ptr _raw_buff = (**_info.ibuff_)[svideo::consts::offs::raw];

  _raw_buff->balloc (svideo::AllocBuffInfo (_req_width, _req_height, _req_stride, ::libs::helpers::uids::minor::rgb24));
  svideo::helpers::override_data (*_raw_buff, 0, _req_size);
  return;
}

}}}      // namespace dlls::convertors::all2hsl
