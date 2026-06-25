#pragma once
/**
\file       empty-mutex.hpp
\author     Erashov Anton erashov2026@proton.me
\date       07.10.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::thread
{
struct EmptyMutex final {
  EmptyMutex ()  = default;
  ~EmptyMutex () = default;

  void
  lock ()
  {
  }

  void
  unlock ()
  {
  }

  bool
  try_lock ()
  {
    return true;
  }
};
}   // namespace libs::helpers::thread
