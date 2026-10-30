#pragma once
/**
\file       check-ptr-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       08.10.2024
*/

namespace libs::utility::checks
{
template< typename T >
  requires (
    std::is_pointer_v< T >)
T
ptr (T val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
  return val;
}


template< typename T >
const std::shared_ptr< T >&
ptr (const std::shared_ptr< T >& val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
  return val;
}


template< typename T >
const std::weak_ptr< T >&
ptr (const std::weak_ptr< T >& val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
  return val;
}


template< typename T >
  requires (
    std::is_pointer_v< T >)
void
must_valid_ptr (T val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
}


template< typename T >
void
must_valid_ptr (const std::shared_ptr< T >& val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
}


template< typename T >
void
must_valid_ptr (const std::weak_ptr< T >& val)
{
  ::libs::utility::checks::throw_ifn ((bool) val);
}
}   // namespace libs::utility::checks
