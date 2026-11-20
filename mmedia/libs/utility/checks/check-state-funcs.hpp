#pragma once
/**
\file       check-state-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2026
*/

namespace libs::utility::checks
{
auto assert_hard (bool, std::string_view = "", const std::source_location& = std::source_location::current ()) -> void;
auto assert_soft (bool, std::string_view = "", const std::source_location& = std::source_location::current ()) -> void;
auto throw_exception (std::string_view, const std::source_location& = std::source_location::current ()) -> void;
auto throw_if (bool, std::string_view = "", const std::source_location& = std::source_location::current ()) -> void;
auto throw_ifn (bool, std::string_view = "", const std::source_location& = std::source_location::current ()) -> void;
auto test (bool, std::string_view = "", const std::source_location& = std::source_location::current ()) -> void;
auto mark (std::string_view, const std::source_location& = std::source_location::current ()) -> void;
auto mark_i64 (std::string_view, const std::source_location& = std::source_location::current ()) -> void;
auto mark_todo (std::string_view, const std::source_location& = std::source_location::current ()) -> void;
}   // namespace libs::utility::checks
