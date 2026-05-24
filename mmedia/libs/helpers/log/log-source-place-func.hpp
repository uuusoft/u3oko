#pragma once
/**
\file       log-source-place-func.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.04.2026
\project    u3_helpers_lib
*/

namespace libs::helpers::log
{
std::string get_text_source_place (const std::source_location& loc = std::source_location::current ());
}   // namespace libs::helpers::log
