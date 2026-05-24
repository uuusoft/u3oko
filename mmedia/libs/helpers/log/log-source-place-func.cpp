/**
\file       log-source-place-func.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.04.2026
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "log-source-place-func.hpp"

namespace libs::helpers::log
{
inline std::string_view
clear_func_name (const std::string_view func_name)
{
#if 1
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


inline std::string_view
clear_file_name (const std::string_view file_name)
{
  constexpr auto len_mmedia = sizeof ("mmedia");
  const auto     beg        = file_name.find ("mmedia");
  if (std::string::npos != beg && beg)
  {
    return file_name.substr (beg + len_mmedia);
  }
  return file_name;
}


std::string
get_text_source_place (const std::source_location& loc)
{
  const auto func_name = clear_func_name (loc.function_name ());
  const auto file_name = clear_file_name (loc.file_name ());
  return std::string (file_name) + '[' + std::to_string (loc.line ()) + ':' + std::to_string (loc.column ()) + "] " + std::string (func_name);
}
}   // namespace libs::helpers::log
