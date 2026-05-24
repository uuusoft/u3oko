/**
\file       vgen-conv3_11-transform_funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-conv3_11-includes_int.hpp"
#include "vgen-conv3_11-info-filter-dll.hpp"
#include "vgen-conv3_11-filter-dll.hpp"

namespace dlls::gens::vgen_conv3_11
{
void
Filter::transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }
  itransform ();
}


void
Filter::itransform ()
{
  convolution_buf ();
}
}   // namespace dlls::gens::vgen_conv3_11
