/**
\file       enum-convs.cpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "enum-convs.hpp"

namespace libs::events_base::props::videos::generic::convolution
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Convs& src)
{
  jvs = { "convolution_type", U3_CAST_UINT32_FORCE (src) };
}


auto
tag_invoke (::boost::json::value_to_tag< Convs >, const ::boost::json::value& jvs) -> Convs
{
  return ::libs::utility::casts::static_cast_helper< Convs > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base::props::videos::generic::convolution
