/**
\file       override-codec-data-type.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "override-codec-data-type.hpp"

namespace libs::ievents::props::videos::generic::codec
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Writes& src)
{
  jvs = {
    { "override_codec_data", U3_CAST_UINT64_FORCE (src) }
  };
}


Writes
tag_invoke (::boost::json::value_to_tag< Writes >, const ::boost::json::value& jvs)
{
  const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::helpers::casts::static_cast_helper< Writes > (::libs::helpers::json::get_uint32 (obj.at ("override_codec_data")));
}
}   // namespace libs::ievents::props::videos::generic::codec
