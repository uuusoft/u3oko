/**
\file       enum-writes.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "enum-writes.hpp"

namespace libs::events_base::props::videos::generic::codec
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Writes& src)
{
  jvs = {
    { "override_codec_data", U3_CAST_UINT64_FORCE (src) }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< Writes >, const ::boost::json::value& jvs) -> Writes
{
  const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::utility::casts::static_cast_helper< Writes > (::libs::utility::json::get_uint32 (obj.at ("override_codec_data")));
}
}   // namespace libs::events_base::props::videos::generic::codec
