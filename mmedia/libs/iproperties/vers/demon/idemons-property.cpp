/**
\file       idemons-property.cpp
\date       02.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-iproperties-includes_int.hpp"
#include "idemons-property.hpp"

namespace libs::iproperties::vers::demon
{
IDemonsProperty::IDemonsProperty () :
  all2mem_ (nullptr),
  all2buf_ (nullptr),
  all2optim_ (nullptr),
  all2mevents_ (nullptr)
{
}


IDemonsProperty::~IDemonsProperty ()
{
}


syn::BlockMemAllocatorProxy::raw_ptr
IDemonsProperty::get_mem_lockfree () const
{
  U3_CHECK (all2mem_, "all2mem_");
  return all2mem_;
}


void
IDemonsProperty::set_mem_lockfree (syn::BlockMemAllocatorProxy::raw_ptr ptr)
{
  all2mem_ = ptr;
}


syn::BufAllocatorProxy::raw_ptr
IDemonsProperty::get_bufs_lockfree () const
{
  U3_CHECK (all2buf_, "all2buf_");
  return all2buf_;
}


void
IDemonsProperty::set_bufs_lockfree (syn::BufAllocatorProxy::raw_ptr ptr)
{
  all2buf_ = ptr;
}


::libs::proxy::IOptimProxy::raw_ptr
IDemonsProperty::get_optim_lockfree () const
{
  U3_CHECK (all2optim_, "all2optim_");
  return all2optim_;
}


void
IDemonsProperty::set_optim_lockfree (::libs::proxy::IOptimProxy::raw_ptr ptr)
{
  all2optim_ = ptr;
}


::libs::proxy::IEventsProxy::raw_ptr
IDemonsProperty::get_events_lockfree () const
{
  U3_CHECK (all2mevents_, "all2mevents_")
  return all2mevents_;
}


void
IDemonsProperty::set_events_lockfree (::libs::proxy::IEventsProxy::raw_ptr ptr)
{
  all2mevents_ = ptr;
}


bool
IDemonsProperty::self_test_int () const
{
  U3_ASSERT (all2mem_);
  U3_ASSERT (all2buf_);
  U3_ASSERT (all2optim_);
  U3_ASSERT (all2mevents_);
  return all2mem_ && all2buf_ && all2optim_ && all2mevents_ ? true : false;
}


void*
IDemonsProperty::cast2top_int ()
{
  return this;
}
}   // namespace libs::iproperties::vers::demon
