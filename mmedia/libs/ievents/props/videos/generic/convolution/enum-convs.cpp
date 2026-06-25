/**
\file       enum-convs.cpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "enum-convs.hpp"

namespace libs::ievents::props::videos::generic::convolution
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Convs& src)
{
  jvs = { "convolution_type", U3_CAST_UINT32_FORCE (src) };
}


Convs
tag_invoke (::boost::json::value_to_tag< Convs >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< Convs > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ievents::props::videos::generic::convolution
