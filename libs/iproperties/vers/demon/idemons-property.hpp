//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       idemons-property.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties { namespace vers { namespace demon {
//  syn
using ::libs::ievents::props::application::ApplicationProp;
using ::utils::mem_functs::impl::BlockMemAllocatorProxy;
using ::utils::dbuffs::allocator::BuffAllocatorProxy;
using ::libs::optim::io::IOptimProxy;
using ::libs::events::io::IEventsProxy;
/**
  \brief  Тип для разделения свойств, общих для всего приложения, между всеми модулями системы.
  */
class IDemonsProperty final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IDemonsProperty);

  IDemonsProperty () :
    all2mem_ (nullptr),
    all2buff_ (nullptr),
    all2optim_ (nullptr),
    all2mevents_ (nullptr)
  {}

  virtual ~IDemonsProperty ()
  {}

  BlockMemAllocatorProxy::raw_ptr
  get_mem_lockfree () const
  {
    return all2mem_;
  }

  void
  set_mem_lockfree (BlockMemAllocatorProxy::raw_ptr _ptr)
  {
    all2mem_ = _ptr;
    return;
  }

  BuffAllocatorProxy::raw_ptr
  get_buffs_lockfree () const
  {
    return all2buff_;
  }

  void
  set_buffs_lockfree (BuffAllocatorProxy::raw_ptr _ptr)
  {
    all2buff_ = _ptr;
    return;
  }

  IOptimProxy::raw_ptr
  get_optim_lockfree () const
  {
    return all2optim_;
  }

  void
  set_optim_lockfree (IOptimProxy::raw_ptr _ptr)
  {
    all2optim_ = _ptr;
    return;
  }

  IEventsProxy::raw_ptr
  get_events_lockfree () const
  {
    return all2mevents_;
  }

  void
  set_events_lockfree (IEventsProxy::raw_ptr _ptr)
  {
    all2mevents_ = _ptr;
    return;
  }


  private:
  virtual bool
  self_test_int () const override
  {
    UASSERT (all2mem_);
    UASSERT (all2buff_);
    UASSERT (all2optim_);
    UASSERT (all2mevents_);
    return all2mem_ && all2buff_ && all2optim_ && all2mevents_ ? true : false;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }

  BlockMemAllocatorProxy::raw_ptr all2mem_;          //< Интерфейс для работы с блочной памятью.
  BuffAllocatorProxy::raw_ptr     all2buff_;         //< Интерфейс для работы с буферами данных.
  IOptimProxy::raw_ptr            all2optim_;        //< Интерфейс для работы с реализациями алгоритмов.
  IEventsProxy::raw_ptr           all2mevents_;      //< Интерфейс для создания объектов-свойств по текстовым идентификаторорам.
};

}}}}      // namespace libs::iproperties::vers::demon
