#pragma once
/**
\file       enum-impl-runs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
*/

namespace modules::mstorage::appl::impl
{
enum class ImplRuns : std::uint32_t
{
  run     = 0x00,   //<
  stop    = 0x01,   //<
  unknown = 0xFF    //<
};

// EAI-REFACT
inline std::string
to_string (const ImplRuns& val)
{
  switch (val)
  {
  case ImplRuns::run:
    return "run";
  case ImplRuns::stop:
    return "stop";
  case ImplRuns::unknown:
    return "unknown";
  }
  U3_XLOG_WARN ("unknown type ImplRuns:{}", U3_CAST_UINT32_FORCE (val));
  return "x81";
}
}   // namespace modules::mstorage::appl::impl
