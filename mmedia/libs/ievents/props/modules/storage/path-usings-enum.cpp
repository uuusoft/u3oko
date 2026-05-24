/**
\file       path-usings-enum.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "path-usings-enum.hpp"

namespace libs::ievents::props::modules::storage
{
PathUsings
str2using_path (const std::string& str)
{
  static const std::unordered_map< std::string, const PathUsings > strs2paths = {
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
}   // namespace libs::ievents::props::modules::storage
