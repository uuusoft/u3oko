/**
\file       enum-calls.cpp
\date       04.03.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "../libs-link-includes_int.hpp"
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

// EAI-REFACT
auto
to_request (const std::string& val) -> Calls
{
#if 1
  static const boost::unordered_flat_map< std::string, const Calls, ::libs::utility::utils::TransparentStringHash, std::equal_to<> > vals = {
    { "set", Calls::set },
    { "request", Calls::request },
    { "answer", Calls::answer },
    { "generate", Calls::generate },
    { "unknown", Calls::unknown }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_XLOG_WARN ("unknown Calls:{}", val);
    return Calls::request;
  }
  return finger->second;
#else
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
  U3_XLOG_WARN ("unknown Calls:{}", str);
  return Calls::request;
#endif
}
}   // namespace libs::link::details
