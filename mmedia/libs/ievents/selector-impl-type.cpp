/**
\file       selector-impl-type.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.03.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "selector-impl-type.hpp"

namespace libs::ievents
{
std::string
to_string (const SelectorImpls& val)
{
  switch (val)
  {
  case SelectorImpls::automatic:
    return "automatic";
  case SelectorImpls::software:
    return "software";
  case SelectorImpls::hardware:
    return "hardware";
  case SelectorImpls::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown SelectorImpls" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown SelectorImpls";
  }
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const SelectorImpls& src)
{
  jv = U3_CAST_UINT32_FORCE (src);
}


SelectorImpls
tag_invoke (::boost::json::value_to_tag< SelectorImpls >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< SelectorImpls > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ievents
