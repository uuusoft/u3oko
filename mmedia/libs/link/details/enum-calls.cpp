/**
\file       enum-calls.cpp
\date       04.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/
#include "../_make/libs-link-includes_int.hpp"
#include "enum-calls.hpp"

namespace libs::link::details
{
auto
to_string (const Calls& val) -> const std::string&
{
  static const boost::unordered_flat_map< Calls, const std::string > vals = {
    { Calls::set, "set" },
    { Calls::request, "request" },
    { Calls::answer, "answer" },
    { Calls::generate, "generate" },
    { Calls::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    finger = vals.find (Calls::unknown);
  }
  return finger->second;
}


auto
to_request (const std::string& str) -> Calls
{
  if ("set" == str)
  {
    return Calls::set;
  }
  if ("request" == str)
  {
    return Calls::request;
  }
  if ("answer" == str)
  {
    return Calls::answer;
  }
  if ("generate" == str)
  {
    return Calls::generate;
  }
  U3_XLOG_WARN ("unknown text Calls " + str);
  return Calls::request;
}
}   // namespace libs::link::details
