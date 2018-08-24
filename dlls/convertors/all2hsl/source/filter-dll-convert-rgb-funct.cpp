//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-convert_from_rgb_funct.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_all2hsl
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace convertors { namespace all2hsl {

void
Filter::convert_buffs_from_rgb ()
{
  XULOG_TRACE ("Filter::convert_buffs_from_rgb: beg");
  IVideoBuff::raw_ptr _hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuff_)[svideo::consts::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuff_)[svideo::consts::offs::sat],
    (*pbuff_)[svideo::consts::offs::lit]
  };

  IVideoBuff::raw_ptr      _rcbuff = (*pbuff_)[svideo::consts::offs::raw];
  ::libs::optim::MCallInfo _cinfo;
  InfoMFunct               _tfunct;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_rcbuff));

  if (finfo_.strip_color_)
    {
      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_hsl[2]));

      _tfunct.pfunct_          = TypeConvertAccuracy::best == finfo_.rprops_->atype_ ? &rgb24_to_l_accurate_ : &rgb24_to_l_fast_;
      _tfunct.src_align_.px_x_ = 1;
      _tfunct.dst_align_.px_x_ = 1;
      _tfunct.src_align_.px_y_ = 1;
      _tfunct.dst_align_.px_y_ = 1;
    }
  else
    {
      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_hsl[0]));
      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_hsl[1]));
      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_hsl[2]));

      _tfunct.pfunct_          = &rgb24_to_hsl_;
      _tfunct.src_align_.px_x_ = 1;
      _tfunct.dst_align_.px_x_ = 1;
      _tfunct.src_align_.px_y_ = 1;
      _tfunct.dst_align_.px_y_ = 1;
    }

  if (!finfo_.rprops_->debug_skip_transform_)
    {
      XULOG_TRACE ("Filter::convert_buffs_from_rgb: before transform");
      pthreads_->mcall (_tfunct, _cinfo);
      XULOG_TRACE ("Filter::convert_buffs_from_rgb: after transform");
    }

  for (IVideoBuff::raw_ptr _cbuff : _hsl)
    {
      if (!_cbuff)
        {
          continue;
        }

      _cbuff->set_mem_var (
        ::utils::dbuffs::TypeMemVar::size_data,
        _cbuff->get_dim_var (svideo::TypeDimVar::height) * _cbuff->get_dim_var (svideo::TypeDimVar::stride));
      //_cbuff->fill( rand() % 255 );//debug
    }
  XULOG_TRACE ("Filter::convert_buffs_from_rgb: end");
  return;
}

}}}      // namespace dlls::convertors::all2hsl
