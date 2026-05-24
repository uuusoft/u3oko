/**
\file       type-gradient.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.06.2022

\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "type-gradient.hpp"

namespace libs::ievents::props::videos::generic::gradient
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Gradients& src)
{
#if 1
  jv = U3_CAST_UINT32_FORCE (src);
#else
  jv = {
    { "type_gradient", U3_CAST_UINT32 (src) }
  };
#endif
}


Gradients
tag_invoke (::boost::json::value_to_tag< Gradients >, const ::boost::json::value& jv)
{
  Gradients ret = Gradients::unknown;
#if 1
  ret = U3_CAST_STATIC< Gradients > (::libs::helpers::json::get_uint32 (jv));
#else
  const ::boost::json::object& obj = jv.as_object ();
  ret                              = U3_CAST_STATIC< Gradients > (::libs::helpers::json::get_uint32 (obj.at ("type_gradient")));
#endif
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::gradient
