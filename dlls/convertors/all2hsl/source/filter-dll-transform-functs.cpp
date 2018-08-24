//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
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
Filter::itransform ()
{
  XULOG_TRACE ("Filter::itransform: beg");
  alloc_buffs ();

  IVideoBuff::raw_ptr _rcbuff = (*pbuff_)[svideo::consts::offs::raw];
  const auto          _format = _rcbuff->get_format ();

  if (_rcbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_TRACE ("Filter::itransform: empty buff, skip convert");
      return;
    }

  if (::libs::helpers::uids::minor::rgb24 == _format)
    {
      XULOG_TRACE ("Filter::itransform: rgb2hsl convert");
      convert_buffs_from_rgb ();
    }
  else if (::libs::helpers::uids::minor::y8 == _format)
    {
      convert_buffs_from_y8 ();
    }
  else if (::libs::helpers::uids::minor::y16 == _format)
    {
      convert_buffs_from_y16 ();
    }
  else
    {
      XULOG_INFO ("Filter::itransform: unknown raw format, skip convert, " << ::libs::helpers::uids::helpers::get_readable_name (_format));
      return;
    }

  flip_y_buffs ();
  duplicate_buffs ();
  alloc_temp_buffs ();

  if (finfo_.strip_color_)
    {
      (*pbuff_)[svideo::consts::offs::hue]->flush ();
      (*pbuff_)[svideo::consts::offs::sat]->flush ();
    }
  return;
}

}}}      // namespace dlls::convertors::all2hsl
