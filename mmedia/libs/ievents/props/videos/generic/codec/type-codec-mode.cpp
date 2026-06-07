/**
\file       type-codec-mode.cpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "type-codec-mode.hpp"

namespace libs::ievents::props::videos::generic::codec
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const CodecModes& src)
{
  jvs = { "codec_mode", U3_CAST_UINT32_FORCE (src) };
}


CodecModes
tag_invoke (::boost::json::value_to_tag< CodecModes >, const ::boost::json::value& jvs)
{
  U3_XLOG_DEV ("CodecModes::tag_invoke::load::begin");
  // const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::helpers::casts::static_cast_helper< CodecModes > (::libs::helpers::json::get_uint32 (jvs.at ("codec_mode")));
}
}   // namespace libs::ievents::props::videos::generic::codec
