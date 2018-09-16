//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       transform_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_conv
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace gens { namespace vgen_conv3_11 {

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
  XULOG_TRACE ("::dlls::gens::vgen_conv3_11Filter::itransform::beg");
  convolution_buff ();
  XULOG_TRACE ("::dlls::gens::vgen_conv3_11Filter::itransform::end");
  return;
}

}}}      // namespace dlls::gens::vgen_conv3_11
