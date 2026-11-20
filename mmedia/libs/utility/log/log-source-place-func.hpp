#pragma once
/**
\file       log-source-place-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.04.2026
*/

namespace libs::utility::log
{
auto clear_func_name (const std::string_view) -> std::string_view;
auto clear_file_name (const std::string_view) -> std::string_view;
auto get_text_source_place (const std::source_location& = std::source_location::current ()) -> std::string;
}   // namespace libs::utility::log
