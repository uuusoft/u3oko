#pragma once
/**
\file       idemons-property.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/

// REFACT
namespace libs::proxy
{
class IOptimProxy;
class IEventsProxy;
}   // namespace libs::proxy

namespace libs::iproperties::vers::demon
{
/// Тип для разделения свойств, общих для всего приложения, между всеми модулями системы
class IDemonsProperty final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IDemonsProperty)

  IDemonsProperty ();
  virtual ~IDemonsProperty () = default;

  auto get_mem_lockfree () const -> syn::BlockMemAllocatorProxy::raw_ptr;
  auto set_mem_lockfree (syn::BlockMemAllocatorProxy::raw_ptr ptr) -> void;
  auto get_bufs_lockfree () const -> syn::BufAllocatorProxy::raw_ptr;
  auto set_bufs_lockfree (syn::BufAllocatorProxy::raw_ptr ptr) -> void;
  auto get_optim_lockfree () const -> ::libs::proxy::IOptimProxy*;
  auto set_optim_lockfree (::libs::proxy::IOptimProxy* ptr) -> void;
  auto get_events_lockfree () const -> ::libs::proxy::IEventsProxy*;
  auto set_events_lockfree (::libs::proxy::IEventsProxy* ptr) -> void;

  private:
  // ::libs::properties::ISharedProperty
  virtual bool  self_test_int () const override;
  virtual void* cast2top_int () override;

  std::atomic< syn::BlockMemAllocatorProxy::raw_ptr > all2mem_     = nullptr;   //< Интерфейс для работы с блочной памятью
  std::atomic< syn::BufAllocatorProxy::raw_ptr >      all2buf_     = nullptr;   //< Интерфейс для работы с буферами данных
  std::atomic< ::libs::proxy::IOptimProxy* >          all2optim_   = nullptr;   //< Интерфейс для работы с реализациями алгоритмов
  std::atomic< ::libs::proxy::IEventsProxy* >         all2mevents_ = nullptr;   //< Интерфейс для создания объектов-свойств по текстовым идентификаторорам
};
}   // namespace libs::iproperties::vers::demon
