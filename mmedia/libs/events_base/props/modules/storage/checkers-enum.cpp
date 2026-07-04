/**
\file       checkers-enum.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../events-base-includes_int.hpp"
#include "checkers-enum.hpp"

namespace libs::events_base::props::modules::storage
{
auto
str2checker_storage (const std::string& str) -> Checkers
{
  static const boost::unordered_flat_map< std::string, const Checkers > strs2checkers = {
    { "", Checkers::start_stop },
    { "start_stop", Checkers::start_stop },
    { "disabled", Checkers::disabled },
    { "periodicaly", Checkers::periodicaly },
    { "after_every_write_operation", Checkers::after_every_write_operation }
  };

  auto find = strs2checkers.find (str);
  if (strs2checkers.end () == find)
  {
    U3_XLOG_WARN ("convert str2checker_storage " + str);
    return Checkers::start_stop;
  }
  return find->second;
}
}   // namespace libs::events_base::props::modules::storage
