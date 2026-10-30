#pragma once
/**
\file       empty-mutex.hpp
\author     Erashov Anton erashov2026@proton.me
\date       07.10.2024
*/

namespace libs::utility::thread
{
struct EmptyMutex final {
  EmptyMutex ()  = default;
  ~EmptyMutex () = default;

  void
  lock ()
  {
  }

  auto
  unlock () -> void
  {
  }

  auto
  try_lock () -> bool
  {
    return true;
  }
};
}   // namespace libs::utility::thread
