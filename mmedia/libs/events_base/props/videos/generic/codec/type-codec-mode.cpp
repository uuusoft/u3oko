/**
\file       type-codec-mode.cpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "enum-codec-modes.hpp"

namespace libs::events_base::props::videos::generic::codec
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const CodecModes& src)
{
  jvs = { "codec_mode", U3_CAST_UINT32_FORCE (src) };
}


auto
tag_invoke (::boost::json::value_to_tag< CodecModes >, const ::boost::json::value& jvs) -> CodecModes
{
  U3_XLOG_DEV ("CodecModes::tag_invoke::load::begin");
  // const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::utility::casts::static_cast_helper< CodecModes > (::libs::utility::json::get_uint32 (jvs.at ("codec_mode")));
}
}   // namespace libs::events_base::props::videos::generic::codec
