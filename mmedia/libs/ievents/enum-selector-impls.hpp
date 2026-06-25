#pragma once
/**
\file       enum-selector-impls.hpp
\author     Erashov Anton erashov2026@proton.me
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

auto to_string (const SelectorImpls&) -> std::string;
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const SelectorImpls&) -> void;
auto tag_invoke (::boost::json::value_to_tag< SelectorImpls >, const ::boost::json::value&) -> SelectorImpls;
}   // namespace libs::ievents
