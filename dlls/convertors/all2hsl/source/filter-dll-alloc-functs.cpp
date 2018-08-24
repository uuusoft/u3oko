//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-alloc_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace convertors { namespace all2hsl {

void
Filter::alloc_buffs ()
{
  XULOG_TRACE ("Filter::alloc_buffs: beg");
  IVideoBuff::raw_ptr _braw      = (*pbuff_)[svideo::consts::offs::raw];
  auto                _base_buff = (*pbuff_)[pbuff_->get_indx_base_buff ()];
  const auto          _width     = _base_buff->get_dim_var (svideo::TypeDimVar::width);
  const auto          _height    = _base_buff->get_dim_var (svideo::TypeDimVar::height);
  const auto          _format    = _base_buff->get_format ();

  finfo_.strip_color_ = finfo_.rprops_->strip_color_ || (::libs::helpers::uids::minor::rgb24 != _braw->get_format ());

  XULOG_TRACE ("Filter::alloc_buffs: width =" << _width << ", height=" << _height << ", finfo_.rprops_->strip_color_=" << finfo_.rprops_->strip_color_ << ", finfo_.strip_color=" << finfo_.strip_color_ << ", " << ::libs::helpers::uids::helpers::get_readable_name (_braw->get_format ()));

  IVideoBuff::raw_ptr _hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuff_)[svideo::consts::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuff_)[svideo::consts::offs::sat],
    (*pbuff_)[svideo::consts::offs::lit]
  };

  for (IVideoBuff::raw_ptr _cbuff : _hsl)
    {
      if (!_cbuff)
        {
          continue;
        }

      _cbuff->balloc (
        svideo::AllocBuffInfo (
          _width,
          _height,
          0,
          ::libs::helpers::uids::minor::y16,
          svideo::TypeCheckDim::enable_check,
          ::utils::dbuffs::TypeFlagsBuff::convolution_support));
    }
  XULOG_TRACE ("Filter::alloc_buffs: end");
  return;
}


void
Filter::alloc_temp_buffs ()
{
  //  Резервируем память под второстепенные буфера, связанные с основным.
#if 0
  const IVideoBuff::raw_ptr _l16_buff     = (*pbuff_)[svideo::consts::offs::lit];
  const off_buff_type       _indx_buffs[] = { svideo::consts::offs::temp1, svideo::consts::offs::temp2 };

  for (const off_buff_type& _indx_buff : _indx_buffs)
    {
      IVideoBuff::raw_ptr _tbuff = (*pbuff_)[_indx_buff];
      _tbuff->clone (_l16_buff, 0.0f);
    }
#endif
  return;
}

}}}      // namespace dlls::convertors::all2hsl
