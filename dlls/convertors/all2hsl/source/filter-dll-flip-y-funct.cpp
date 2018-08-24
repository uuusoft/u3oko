//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-flip_y_funct.cpp
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
Filter::flip_y_buffs ()
{
  if (!finfo_.rprops_->flip_y_)
    {
      return;
    }

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

      //  sync y
      ::libs::optim::MCallInfo _cinfo;
      InfoMFunct               _tfunct (&flip_y_);

      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_cbuff));
      pthreads_->mcall (_tfunct, _cinfo, 1);
    }

  return;
}

}}}      // namespace dlls::convertors::all2hsl
