#pragma once
/**
\file       saturation-casts-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_helpers_lib
*/

namespace libs::utility::casts
{
template< typename TTin, typename TTout >
  requires (
    sizeof (TTin) >= sizeof (TTout) &&
    std::is_arithmetic_v< TTin > &&
    std::is_arithmetic_v< TTout > &&
    !std::is_same_v< TTin, TTout >)
constexpr auto
saturation_cast (const TTin& val) -> TTout
{
  if (val < std::numeric_limits< TTout >::min ())
  {
    return std::numeric_limits< TTout >::min ();
  }
  if (val > std::numeric_limits< TTout >::max ())
  {
    return std::numeric_limits< TTout >::max ();
  }
  return ::libs::utility::casts::static_cast_helper< TTout > (val);
}
}   // namespace libs::utility::casts
