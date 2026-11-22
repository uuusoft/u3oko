#pragma once
/**
\file       get-module-version-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.10.2024
*/

namespace libs::utility::log
{
inline auto
get_module_version () -> std::string
{
  return std::format (
    "{}.{}.{} build time:{} compilers-ids:{}",
    ::configure::project_ver_major,
    ::configure::project_ver_minor,
    ::configure::git_hash,
    ::configure::start_build_time,
    ::configure::compilers_info);
}
}   // namespace libs::utility::log
