#pragma once
/**
\file       get_sorted_files_func.hpp
\date       05.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_lib_helpers
*/

namespace libs::utility::files
{
std::vector< std::string > get_sort_by_time_folders (const std::string& path2sessions);
std::vector< std::string > get_sort_by_time_files (const std::string& path2session);
}   // namespace libs::utility::files
