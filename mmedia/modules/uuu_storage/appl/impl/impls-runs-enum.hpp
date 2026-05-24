#pragma once
/**
\file       impls-runs-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl
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
  U3_XLOG_WARN ("unknown type ImplRuns" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
  return "x81";
}
}   // namespace modules::uuu_storage::appl::impl
