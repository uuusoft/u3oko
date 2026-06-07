/**
\file       ishared-property.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_properties_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "ishared-property.hpp"

namespace libs::properties
{
bool
ISharedProperty::self_test () const
{
  lock_type lock (mtx_);
  return self_test_int ();
}


void*
ISharedProperty::cast2top ()
{
  auto ret = cast2top_int ();
  U3_ASSERT (ret);
  return ret;
}


ISharedProperty::sync_type&
ISharedProperty::get_sync ()
{
  return mtx_;
}
}   // namespace libs::properties
