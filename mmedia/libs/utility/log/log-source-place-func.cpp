/**
\file       log-source-place-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.04.2026
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "log-source-place-func.hpp"

namespace libs::utility::log
{
inline auto
clear_func_name (const std::string_view func_name) -> std::string_view
{
#if 1
  return "";
  return func_name;
#else
  const auto beg = func_name.find ("(");
  if (std::string::npos != beg && beg)
  {
    return func_name.substr (0, beg);
  }
  return func_name;
#endif
}


inline auto
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
get_text_source_place (const std::source_location& loc) -> std::string
{
  const auto func_name = clear_func_name (loc.function_name ());
  const auto file_name = clear_file_name (loc.file_name ());
  return std::string (file_name) + '[' + std::to_string (loc.line ()) + ':' + std::to_string (loc.column ()) + "] " + std::string (func_name);
}
}   // namespace libs::utility::log
