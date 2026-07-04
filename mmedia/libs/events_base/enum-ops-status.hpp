#pragma once
/**
\file       enum-ops-status.hpp
\author     Erashov Anton erashov2026@proton.me
\date       10.03.2022
\project    u3_events_base_lib
*/

namespace libs::events_base
{
enum class OpsStatus : std::uint32_t
{
  success = 0x00,   //<
  failed  = 0x01,   //<
  mixed   = 0x02,   //<
  unset   = 0x03,   //<
  unknown = 0xFF    //<
};

inline constexpr OpsStatus
to_ops_status_type (std::uint32_t val)
{
  return ::libs::utility::casts::static_cast_helper< OpsStatus > (val);
}

auto to_string (const OpsStatus&) -> const std::string&;
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const OpsStatus&) -> void;
auto tag_invoke (::boost::json::value_to_tag< OpsStatus >, const ::boost::json::value&) -> OpsStatus;
}   // namespace libs::events_base
