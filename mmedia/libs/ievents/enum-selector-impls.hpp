#pragma once
/**
\file       enum-selector-impls.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.03.2022
\project    u3_ievents_lib
*/

namespace libs::ievents
{
enum class SelectorImpls : std::uint32_t
{
  automatic = 0x00,   //<
  software  = 0x01,   //<
  hardware  = 0x02,   //<
  unknown   = 0xFF    //<
};

inline constexpr SelectorImpls
to_selector_impl_type (std::uint32_t val)
{
  return ::libs::helpers::casts::static_cast_helper< SelectorImpls > (val);
}

std::string   to_string (const SelectorImpls& val);
void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SelectorImpls& src);
SelectorImpls tag_invoke (::boost::json::value_to_tag< SelectorImpls >, const ::boost::json::value& jvs);
}   // namespace libs::ievents
