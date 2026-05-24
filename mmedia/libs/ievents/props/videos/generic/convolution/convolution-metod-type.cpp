/**
\file       convolution-metod-type.cpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "convolution-metod-type.hpp"

namespace libs::ievents::props::videos::generic::convolution
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Convs& src)
{
  jv = { "convolution_type", U3_CAST_UINT32_FORCE (src) };
}


Convs
tag_invoke (::boost::json::value_to_tag< Convs >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< Convs > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ievents::props::videos::generic::convolution
