#pragma once
/**
\file       sql-resource-managment-helpers.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       06.06.2022
\project    mevents
*/

namespace libs::helpers::sqlite
{
class MemoryHandler final
{
  public:
  U3_HELPER_DISABLE_ACOPY_TYPE (MemoryHandler)
  MemoryHandler () = default;
  ~MemoryHandler ();

  void** update ();
  void*  get ();

  template< typename TType >
  TType*
  update_as ()
  {
    return ::libs::helpers::casts::reinterpret_cast_helper< TType* > (update ());
  }

  template< typename TType >
  TType
  get_as ()
  {
    return ::libs::helpers::casts::reinterpret_cast_helper< TType > (get ());
  }

  private:
  void* buf_ = nullptr;
};
}   // namespace libs::helpers::sqlite
