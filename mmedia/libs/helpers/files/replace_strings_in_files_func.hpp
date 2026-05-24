#pragma once
/**
\file       replace_strings_in_files_func.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       25.10.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::files
{
void
replace_strings_in_files (
  const std::string&                                     path2folder,
  const ::libs::helpers::strings::syn::replace_val_type* vals,
  const std::uint32_t                                    count_vals,
  const std::string&                                     files_mask = "");
}   // namespace libs::helpers::files
