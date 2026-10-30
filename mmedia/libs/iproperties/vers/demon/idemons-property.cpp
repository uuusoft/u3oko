/**
\file       idemons-property.cpp
\date       02.03.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../libs-iproperties-includes_int.hpp"
#include "idemons-property.hpp"

namespace libs::iproperties::vers::demon
{
IDemonsProperty::IDemonsProperty () = default;


auto
IDemonsProperty::get_mem_lockfree () const -> syn::BlockMemAllocatorProxy::raw_ptr
{
  ::libs::utility::checks::throw_ifn (all2mem_, "empty all2mem");
  return all2mem_;
}


void
IDemonsProperty::set_mem_lockfree (syn::BlockMemAllocatorProxy::raw_ptr ptr)
{
  all2mem_ = ptr;
}


auto
IDemonsProperty::get_bufs_lockfree () const -> syn::BufAllocatorProxy::raw_ptr
{
  ::libs::utility::checks::throw_ifn (all2buf_, "empty all2buf");
  return all2buf_;
}


void
IDemonsProperty::set_bufs_lockfree (syn::BufAllocatorProxy::raw_ptr ptr)
{
  all2buf_ = ptr;
}


auto
IDemonsProperty::get_optim_lockfree () const -> ::libs::proxy::IOptimProxy::raw_ptr
{
  ::libs::utility::checks::throw_ifn (all2optim_, "empty all2optim");
  return all2optim_;
}


void
IDemonsProperty::set_optim_lockfree (::libs::proxy::IOptimProxy::raw_ptr ptr)
{
  all2optim_ = ptr;
}


auto
IDemonsProperty::get_events_lockfree () const -> ::libs::proxy::IEventsProxy::raw_ptr
{
  ::libs::utility::checks::throw_ifn (all2mevents_, "empty all2mevents");
  return all2mevents_;
}


void
IDemonsProperty::set_events_lockfree (::libs::proxy::IEventsProxy::raw_ptr ptr)
{
  all2mevents_ = ptr;
}


auto
IDemonsProperty::self_test_int () const -> bool
{
  ::libs::utility::checks::throw_ifn (all2mem_);
  ::libs::utility::checks::throw_ifn (all2buf_);
  ::libs::utility::checks::throw_ifn (all2optim_);
  ::libs::utility::checks::throw_ifn (all2mevents_);
  return all2mem_ && all2buf_ && all2optim_ && all2mevents_ ? true : false;
}


auto
IDemonsProperty::cast2top_int () -> void*
{
  return this;
}
}   // namespace libs::iproperties::vers::demon
