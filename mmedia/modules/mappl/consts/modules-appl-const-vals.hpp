#pragma once
/**
\file       modules-appl-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace modules::mappl
{
using main_appl_func_type = int (int argc, char* argv[]);
}

namespace modules::mappl::consts
{
inline constexpr std::string_view name_mfunc { "main_impl" };   //<
}
