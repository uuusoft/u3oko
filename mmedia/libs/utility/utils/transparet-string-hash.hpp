#pragma once
/**
\file       transparet-string-hash.hpp
\date       20.11.2026
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::utility::utils
{
struct TransparentStringHash {
  using is_transparent = void;

  std::size_t
  operator() (std::string_view sv) const noexcept
  {
    return std::hash< std::string_view > {}(sv);
  }
};
}   // namespace libs::utility::utils
