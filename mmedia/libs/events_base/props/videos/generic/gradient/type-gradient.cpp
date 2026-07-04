/**
\file       type-gradient.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "type-gradient.hpp"

namespace libs::events_base::props::videos::generic::gradient
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Gradients& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


auto
tag_invoke (::boost::json::value_to_tag< Gradients >, const ::boost::json::value& jvs) -> Gradients
{
  return ::libs::utility::casts::static_cast_helper< Gradients > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base::props::videos::generic::gradient
