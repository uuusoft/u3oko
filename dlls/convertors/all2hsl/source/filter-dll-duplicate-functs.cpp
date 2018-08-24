//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-duplicate_functs.cpp
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

namespace dlls { namespace convertors { namespace all2hsl {

void
Filter::duplicate_buffs ()
{
  if (!finfo_.rprops_->duplicate_image_)
    {
      return;
    }

  const IVideoBuff::raw_ptr _l16_buff      = (*pbuff_)[svideo::consts::offs::lit];
  IVideoBuff::raw_ptr       _copy_l16_buff = (*pbuff_)[consts::dupl_l];

  _copy_l16_buff->clone (_l16_buff, 100.0f);

  if (finfo_.strip_color_)
    {
      return;
    }

  const IVideoBuff::raw_ptr _h16_buff      = (*pbuff_)[svideo::consts::offs::hue];
  const IVideoBuff::raw_ptr _s16_buff      = (*pbuff_)[svideo::consts::offs::sat];
  IVideoBuff::raw_ptr       _copy_h16_buff = (*pbuff_)[consts::dupl_h];
  IVideoBuff::raw_ptr       _copy_s16_buff = (*pbuff_)[consts::dupl_s];

  _copy_h16_buff->clone (_h16_buff, 100.0f);
  _copy_s16_buff->clone (_s16_buff, 100.0f);
  return;
}

}}}      // namespace dlls::convertors::all2hsl
