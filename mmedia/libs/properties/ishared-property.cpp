/**
\file       ishared-property.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_properties_libs
*/
#include "libs-properties-includes_int.hpp"
#include "ishared-property.hpp"

namespace libs::properties
{
auto
ISharedProperty::self_test () const -> bool
{
  lock_type lock (mtx_);
  return self_test_int ();
}


auto
ISharedProperty::cast2top () -> void*
{
  auto ret = cast2top_int ();
  U3_ASSERT (ret);
  return ret;
}


auto
ISharedProperty::get_sync () -> ISharedProperty::sync_type&
{
  return mtx_;
}
}   // namespace libs::properties
