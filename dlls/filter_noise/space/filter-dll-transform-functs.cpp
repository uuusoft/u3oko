//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace filter_noise { namespace space {

void
Filter::transform_int (TransformInfo& _info)
{
  prepare_transform (_info);

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      return;
    }

  itransform ();
  return;
}


void
Filter::itransform ()
{
  impl_->transform_int (finfo_, pbuff_);
  return;
}

}}}      // namespace dlls::filter_noise::space
