/**
\file       path-usings-enum.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../events-base-includes_int.hpp"
#include "path-usings-enum.hpp"

namespace libs::events_base::props::modules::storage
{
auto
str2using_path (const std::string& str) -> PathUsings
{
  static const boost::unordered_flat_map< std::string, const PathUsings > strs2paths = {
    { "", PathUsings::disabled },
    { "disabled", PathUsings::disabled },
    { "read_only", PathUsings::read_only },
    { "write_only", PathUsings::write_only },
    { "read_write", PathUsings::read_write }
  };

  auto find = strs2paths.find (str);
  if (strs2paths.end () == find)
  {
    U3_XLOG_WARN ("convert str2using_path " + str);
    return PathUsings::disabled;
  }
  return find->second;
}
}   // namespace libs::events_base::props::modules::storage
