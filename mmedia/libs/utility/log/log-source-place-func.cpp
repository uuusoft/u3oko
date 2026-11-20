/**
\file       log-source-place-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.04.2026
*/
#include "../utility-lib-includes_int.hpp"
#include "log-source-place-func.hpp"

namespace libs::utility::log
{
auto
clear_func_name (const std::string_view func_name) -> std::string_view
{
  const auto beg = func_name.find ("(");
  if (std::string::npos != beg && beg)
  {
    return func_name.substr (0, beg);
  }
  return func_name;
}


auto
clear_file_name (const std::string_view file_name) -> std::string_view
{
  constexpr auto len_mmedia = sizeof ("mmedia");
  const auto     beg        = file_name.find ("mmedia");
  if (std::string::npos != beg && beg)
  {
    return file_name.substr (beg + len_mmedia);
  }
  return file_name;
}


auto
get_text_source_place (const std::source_location& place) -> std::string
{
  const auto func_name = clear_func_name (place.function_name ());
  const auto file_name = clear_file_name (place.file_name ());
  return std::string (file_name) + '[' + std::to_string (place.line ()) + ':' + std::to_string (place.column ()) + "] " + std::string (func_name);
}
}   // namespace libs::utility::log
