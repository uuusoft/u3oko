#pragma once
/**
\file       check-ptr-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       08.10.2024
\project    u3_helpers_lib
*/

namespace libs::utility::check
{
template< typename T, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
T
ptr (T val)
{
  U3_ASSERT (val);
  return val;
}


template< typename T >
const std::shared_ptr< T >&
ptr (const std::shared_ptr< T >& val)
{
  U3_ASSERT (val);
  return val;
}


template< typename T >
const std::weak_ptr< T >&
ptr (const std::weak_ptr< T >& val)
{
  U3_ASSERT (val);
  return val;
}


template< typename T, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
void
must_valid_ptr (T val)
{
  U3_ASSERT (val);
}


template< typename T >
void
must_valid_ptr (const std::shared_ptr< T >& val)
{
  U3_ASSERT (val);
}


template< typename T >
void
must_valid_ptr (const std::weak_ptr< T >& val)
{
  U3_ASSERT (val);
}
}   // namespace libs::utility::check
