#pragma once
/**
\file       ishared-property.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  using lock_type = std::lock_guard< sync_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISharedProperty)

  ISharedProperty ();
  virtual ~ISharedProperty ();

  ISharedProperty (const ISharedProperty& src)            = delete;
  ISharedProperty& operator= (const ISharedProperty& src) = delete;

  bool       self_test () const;
  void*      cast2top ();
  sync_type& get_sync ();

  protected:
  //  ISharedProperty interface
  virtual bool  self_test_int () const = 0;
  virtual void* cast2top_int ()        = 0;

  private:
  mutable sync_type mtx_;   //<
};
}   // namespace libs::properties
