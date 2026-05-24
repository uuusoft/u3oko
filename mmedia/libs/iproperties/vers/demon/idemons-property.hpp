#pragma once
/**
\file       idemons-property.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IDemonsProperty)

  IDemonsProperty ();
  virtual ~IDemonsProperty ();

  syn::BlockMemAllocatorProxy::raw_ptr get_mem_lockfree () const;
  void                                 set_mem_lockfree (syn::BlockMemAllocatorProxy::raw_ptr ptr);
  syn::BufAllocatorProxy::raw_ptr      get_bufs_lockfree () const;
  void                                 set_bufs_lockfree (syn::BufAllocatorProxy::raw_ptr ptr);
  ::libs::proxy::IOptimProxy*          get_optim_lockfree () const;
  void                                 set_optim_lockfree (::libs::proxy::IOptimProxy* ptr);
  ::libs::proxy::IEventsProxy*         get_events_lockfree () const;
  void                                 set_events_lockfree (::libs::proxy::IEventsProxy* ptr);

  private:
  // ::libs::properties::ISharedProperty
  virtual bool  self_test_int () const override;
  virtual void* cast2top_int () override;

  std::atomic< syn::BlockMemAllocatorProxy::raw_ptr > all2mem_;       //< Интерфейс для работы с блочной памятью
  std::atomic< syn::BufAllocatorProxy::raw_ptr >      all2buf_;       //< Интерфейс для работы с буферами данных
  std::atomic< ::libs::proxy::IOptimProxy* >          all2optim_;     //< Интерфейс для работы с реализациями алгоритмов
  std::atomic< ::libs::proxy::IEventsProxy* >         all2mevents_;   //< Интерфейс для создания объектов-свойств по текстовым идентификаторорам
};
}   // namespace libs::iproperties::vers::demon
