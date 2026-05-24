#pragma once
/**
\file       empty-mutex.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       07.10.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::thread
{
struct EmptyMutex final {
  EmptyMutex ()
  {
  }

  ~EmptyMutex ()
  {
  }

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
