#pragma once
/**
\file       replace_strings_in_files_func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       25.10.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::files
{
std::uint32_t
replace_strings_in_files (
  const std::string&                    path2folder,
  const strings::syn::replace_val_type* vals,
  const std::uint32_t                   count_vals,
  const std::string&                    files_mask = "");
}   // namespace libs::helpers::files
