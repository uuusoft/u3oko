#pragma once
/**
\file       get-module-version-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.10.2024
\project    u3_helpers_lib
*/

namespace libs::utility::log
{
inline std::string
get_module_version ()
{
  return std::to_string (::configure::project_ver_major) +
         "." + std::to_string (::configure::project_ver_minor) +
         "." + std::string (::configure::git_hash) +
         " build time:" + std::string (::configure::start_build_time) +
         " compilers-ids:" + std::string (::configure::compilers_info);
}
}   // namespace libs::utility::log
