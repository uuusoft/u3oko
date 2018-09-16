//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_mix_mul
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace mixers { namespace mix_multiplier {

void
Filter::transform_int (TransformInfo& _info)
{
  prepare_transform (_info);

  auto& _obuff = (*_info.obuff_);

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      //*_obuff = **_info.ibuff_;
      return;
    }
  if (!_info.ibuff_ || !*_info.ibuff_)
    {
      return;
    }

  //для каждой выходной точки создаем свою копию входного буфера.
  _obuff = std::make_shared<::libs::buffs::Buffs> ();
  _obuff->clone (**_info.ibuff_);
  //_obuff->swap( **_info.ibuff_ );

  const auto& _out_pt_info = finfo_.rprops_->outs_[_info.oindx_];

  for (const ::libs::events::buff::EventBuffsInfo& _indx_buffs : _out_pt_info.srcs2dsts_)
    {
      if (::utils::dbuffs::video::consts::offs::invalid == _indx_buffs.indx_sbuff_)
        {
          continue;
        }
      if (::utils::dbuffs::video::consts::offs::invalid == _indx_buffs.indx_dbuff_)
        {
          continue;
        }
      if (_indx_buffs.indx_sbuff_ == _indx_buffs.indx_dbuff_)
        {
          continue;
        }

      utils::dbuffs::video::IVideoBuff::raw_ptr _src = (*_obuff)[_indx_buffs.indx_sbuff_];

      if (!_src)
        {
          continue;
        }

      if (_src->get_flag (utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      utils::dbuffs::video::IVideoBuff::raw_ptr _dst = (*_obuff)[_indx_buffs.indx_dbuff_];

      if (!_dst)
        {
          UASSERT_SIGNAL ("failed");
          continue;
        }

      _dst->clone (_src, 100.0f);

      if (utils::dbuffs::video::consts::offs::lit == _indx_buffs.indx_dbuff_)
        {
          auto _base_buff = (*pbuff_)[pbuff_->get_indx_base_buff ()];

          _base_buff->set_dim_var (
            ::utils::dbuffs::video::TypeDimVar::width,
            _dst->get_dim_var (::utils::dbuffs::video::TypeDimVar::width));

          _base_buff->set_dim_var (
            ::utils::dbuffs::video::TypeDimVar::height,
            _dst->get_dim_var (::utils::dbuffs::video::TypeDimVar::height));
        }
    }

  return;
}

}}}      // namespace dlls::mixers::mix_multiplier
