/**
\file       type-gradient.cpp
\author     Erashov Anton erashov2026@proton.me
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
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Gradients& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


Gradients
tag_invoke (::boost::json::value_to_tag< Gradients >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< Gradients > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ievents::props::videos::generic::gradient
