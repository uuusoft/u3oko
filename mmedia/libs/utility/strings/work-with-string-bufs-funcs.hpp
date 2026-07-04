#pragma once
/**
\file       work-with-string-bufs-funcs.hpp
\date       23.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::utility::strings::syn
{
using replace_val_type = std::pair< std::string, std::string >;
}

namespace libs::utility::strings
{
bool
inplace_replace_substring (
  const syn::replace_val_type* vals,
  const std::size_t            vals_count,
  std::string&                 buf);

bool
replace_substring (
  const syn::replace_val_type* vals,
  const std::size_t            vals_count,
  const std::string&           srcbuf,
  std::string&                 dstbuf);
}   // namespace libs::utility::strings
