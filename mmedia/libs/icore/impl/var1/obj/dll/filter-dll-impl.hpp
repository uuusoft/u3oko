#pragma once
/**
\file       filter-dll-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.10.2016
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
/// U3-REFACT
/// Вспомогательный тип для реализации фильтров в графе обработке данных
/// \tparam   TTInfoFilterImpl   тип для хранимых свойств, данного фильтра
template< typename TTInfoFilterImpl >
class FilterImpl
{
  public:
  FilterImpl ()
  {
    init_event2func ();
  }

  virtual ~FilterImpl ()
  {
  }

  protected:
  //  internal typess
  using call_catch_func_type = std::function< void (CallInterfInfo& info) >;
  using id_event2func_type   = std::unordered_map< ::libs::events::IEvent::hid_type, call_catch_func_type >;

  // U3-REFACT
  virtual void
  sync_by_events (U3_MARK_UNUSED bool update)
  {
  }

  void
  reset_ptrs ()
  {
    fbinfo_            = nullptr;
    pbuf_              = nullptr;
    pthreads_          = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
    plog_module_props_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_log_lockfree ();

    if (plog_module_props_)
    {
      ::libs::ievents::props::modules::log::g_log_level = ::libs::ievents::props::modules::log::from_raw_val (plog_module_props_->get_val (::libs::ievents::props::modules::log::LogVals::log_level));
    }
  }

  void
  call_gen (CallInterfInfo& info)
  {
    U3_CHECK (info.check (), "failed call_gen ");
    auto find_funct = events2funcs_.find (info.event_->get_mid ());
    if (events2funcs_.end () == find_funct)
    {
      //  Это нормальная ситуация, т.к. часто узлы обработки данных по поддерживают всех сообщений.
      U3_XLOG_DBG ("skip call gen");
      return;
    }

    find_funct->second (info);
  }

  void
  prepare_transform (TransformInfo& info)
  {
    reset_ptrs ();

    fbinfo_ = info.finfo_;
    pbuf_   = (*info.ibuf_).get ();
  }

  void
  prepare_call (CallInterfInfo& info)
  {
    reset_ptrs ();
  }

  libs::icore::impl::var1::obj::FilterInfo* fbinfo_ = nullptr;    //< Указатель на информацию, которая общая для всех фильтров графа U3-REFACT
  TTInfoFilterImpl                          finfo_;               //< Указатель на данные, уникальные для каждого типа фильтра графа
  ::libs::bufs::Bufs*                       pbuf_ = nullptr;      //< Указатеь на буфер с данными, которые обрабатываются на данный момент
  ::libs::optim::mcalls::IMCaller::ptr      pthreads_;            //< Пул потоков для обработки данных
  id_event2func_type                        events2funcs_;        //< Поле для поиска обработчика события по его идентификатору для узла обработки данных
  syn::PropertyLogModuleEvent::craw_ptr     plog_module_props_;   //< Указатель на свойства модуля логирования

  private:
  void
  init_event2func ()
  {
    events2funcs_[::libs::imdata_events::events::ChangeNodeDataEvent::gen_get_mid ()] =
      [this] (CallInterfInfo& info) -> void {
      auto       msg    = ::libs::iproperties::helpers::cast_event< ::libs::imdata_events::events::ChangeNodeDataEvent > (info.event_);
      const auto action = msg->get_action ();

      switch (action)
      {
      case ::libs::imdata_events::events::GraphNodeActions::get: {
        ::libs::imdata_events::events::ChangeNodeDataEvent::events_list_type events;
        // EAI-TEST-???
        for (auto sevent : finfo_.ef_props_)
        {
          events.push_back (::libs::iproperties::helpers::clone_event (sevent.get ()));
        }
        msg->set_events (events);
        break;
      }
      case ::libs::imdata_events::events::GraphNodeActions::set: {
        auto events = msg->get_events ();
        bool update = false;

        for (auto sevent : events)
        {
          for (auto devent : finfo_.ef_props_)
          {
            if (sevent->get_mid () == devent->get_mid ())
            {
              devent->copy (sevent.get ());
              update = true;
            }
          }
        }
        sync_by_events (update);
        finfo_.sync (update);
        break;
      }
      default:
        U3_THROW_EXCEPTION ("failed, unsupported action ChangeNodeDataEvent" + VTOLOG (U3_CAST_UINT32_FORCE (action)));
        break;
      }
    };
#if 0
    events2funcs_[::libs::ievents::props::hardware::InfoCPUEvent::gen_get_mid ()] =
      [this] (CallInterfInfo& info) -> void
    {
      auto msg = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::hardware::InfoCPUEvent > (info.event_);
    };
#endif
  }
};
}   // namespace libs::icore::impl::var1::obj::dll
