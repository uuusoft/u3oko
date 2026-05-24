/**
\file       checkers-enum.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "checkers-enum.hpp"

namespace libs::ievents::props::modules::storage
{
Checkers
str2checker_storage (const std::string& str)
{
  static const std::unordered_map< std::string, const Checkers > strs2checkers = {
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
}   // namespace libs::ievents::props::modules::storage
