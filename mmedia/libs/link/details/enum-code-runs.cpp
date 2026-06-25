/**
\file       enum-code-runs.hppcpp
\author     Erashov Anton erashov2026@proton.me
\date       04.03.2022
\project    u3_link
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-link-includes_int.hpp"
#include "enum-code-runs.hpp"

namespace libs::link::details
{
const std::string&
to_string (const CodeRuns& val)
{
  static const std::unordered_map< CodeRuns, const std::string > vals = {
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
