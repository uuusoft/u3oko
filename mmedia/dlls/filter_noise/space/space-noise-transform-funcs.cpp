/**
\file       space-noise-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_filter_space
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "space-noise-includes_int.hpp"
#include "space-noise-filter-dll.hpp"

namespace dlls::filter_noise::space
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
  impl_->transform_int (id_obj_, *transinfo_, finfo_, pbuf_);
}
}   // namespace dlls::filter_noise::space
