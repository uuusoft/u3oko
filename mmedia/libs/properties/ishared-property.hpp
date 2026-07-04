#pragma once
/**
\file       ishared-property.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_properties_libs
*/

namespace libs::properties
{
class ISharedProperty
{
  public:
  //  ext types
  using sync_type = std::mutex;
  using lock_type = std::scoped_lock< sync_type >;

  U3_ADD_POINTERS_TO_SELF (ISharedProperty)
  U3_ADD_DELETE_MOVE_COPY (ISharedProperty)

  ISharedProperty ()          = default;
  virtual ~ISharedProperty () = default;

  auto self_test () const -> bool;
  auto cast2top () -> void*;
  auto get_sync () -> sync_type&;

  protected:
  //  ISharedProperty interface
  virtual auto self_test_int () const -> bool = 0;
  virtual auto cast2top_int () -> void*       = 0;

  private:
  mutable sync_type mtx_;   //<
};
}   // namespace libs::properties
