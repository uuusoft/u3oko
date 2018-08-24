//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
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

namespace dlls { namespace convertors { namespace all2rgb {

void
Filter::convert_buffs ()
{
  auto       _base_buff = (*pbuff_)[finfo_.rprops_->buff_.indx_sbuff_];
  const auto _px_format = _base_buff->get_format ();
  auto       _rcbuff    = (*pbuff_)[finfo_.rprops_->buff_.indx_dbuff_];
  auto       _tbuff     = (*pbuff_)[svideo::consts::offs::temp1];
  MCallInfo  _cinfo;
  InfoMFunct _tfunct;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_rcbuff));
  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_tbuff));

  _tbuff->set_format (get_out_format_from_format (_px_format));

  _tfunct.pfunct_          = get_funct_for_format (_px_format);
  _tfunct.src_align_.px_x_ = 1;
  _tfunct.dst_align_.px_x_ = 1;
  _tfunct.src_align_.px_y_ = 1;
  _tfunct.dst_align_.px_y_ = 1;

  if (!finfo_.rprops_->debug_skip_transform_)
    {
      pthreads_->mcall (_tfunct, _cinfo);
    }

  //_rcbuff->c1lone( _tbuff, 100.0f );
  _rcbuff->swap (*_tbuff);
  return;
}


void
Filter::itransform ()
{
  alloc_buffs ();
  alloc_temp_buffs ();
  convert_buffs ();

  if (finfo_.rprops_->strip_color_)
    {
      (*pbuff_)[svideo::consts::offs::hue]->flush ();
      (*pbuff_)[svideo::consts::offs::sat]->flush ();
    }
  return;
}

}}}      // namespace dlls::convertors::all2rgb
