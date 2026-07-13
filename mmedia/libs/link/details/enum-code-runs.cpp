/**
\file       enum-code-runs.hppcpp
\author     Erashov Anton erashov2026@proton.me
\date       04.03.2022
\project    u3_link
*/
#include "../_make/libs-link-includes_int.hpp"
#include "enum-code-runs.hpp"

namespace libs::link::details
{
auto
to_string (const CodeRuns& val) -> const std::string&
{
  static const boost::unordered_flat_map< CodeRuns, const std::string > vals = {
    { CodeRuns::usual, "usual" },
    { CodeRuns::dll, "dll" },
    { CodeRuns::appl, "appl" },
    { CodeRuns::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    finger = vals.find (CodeRuns::unknown);
  }
  return finger->second;
}
}   // namespace libs::link::details
