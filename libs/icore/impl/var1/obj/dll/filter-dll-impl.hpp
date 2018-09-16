#pragma once
/**
\file       filter-dll-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.10.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {
/**
\brief    Вспомогательный тип для реальзации фильтров в графе обработке данных.
\tparam   InfoFilterImpl   тип для хранимых свойств, данного фильтра.
*/
template <
  typename InfoFilterImpl>
class FilterImpl
{
  public:

  FilterImpl () :
    pbuff_ (nullptr),
    fbinfo_ (nullptr)
  {
    init_node_event2funct ();
  }

  ~FilterImpl ()
  {}


  protected:
  //  int types
  using call_catch_funct_type = std::function<void(CallInterfInfo& _info)>;
  using id_event2funct_type   = std::map<IEvent::hid_type, call_catch_funct_type>;

  void
  reset_ptrs ()
  {
    fbinfo_   = nullptr;
    pbuff_    = nullptr;
    pthreads_ = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
    return;
  }

  void
  call_gen (CallInterfInfo& _info)
  {
    if (!_info.check ())
      {
        UASSERT_SIGNAL ("failed check CallInterfInfo in call");
        return;
      }

    auto _find_funct = node_event2funct_.find (_info.event_->get_mid ());
    if (node_event2funct_.end () == _find_funct)
      {
        //  Это нормальная ситуация, т.к. часто узлы обработки данных по поддерживают всех сообщений.
        XULOG_TRACE ("failed, try catch event, " << _info.event_->get_mid ());
        return;
      }

    _find_funct->second (_info);
    return;
  }

  void
  prepare_transform (TransformInfo& _info)
  {
    reset_ptrs ();
    fbinfo_ = _info.finfo_;
    pbuff_  = (*_info.ibuff_).get ();
    return;
  }

  void
  prepare_call (CallInterfInfo& _info)
  {
    reset_ptrs ();
    return;
  }

  FilterInfo*         fbinfo_;                //< Указатель на информацию, которая общая для всех фильтров графа.
  InfoFilterImpl      finfo_;                 //< Указатель на данные, уникальные для каждого типа фильтра графа.
  Buffs*              pbuff_;                 //< Указатеь на буфер с данными, которые обрабатываются на данный момент.
  CallerImpl::ptr     pthreads_;              //< Пул потоков для обработки данных.
  id_event2funct_type node_event2funct_;      //< Поле для поиска обработчика события по его идентификатору для узла обработки данных.


  private:
  void
  init_node_event2funct ()
  {
    node_event2funct_[::libs::imdata_events::events::ChangeNodeDataEvent::gen_get_mid ()] = [this](CallInterfInfo& _info) -> void {
      auto _msg = ::libs::iproperties::helpers::cast_event<::libs::imdata_events::events::ChangeNodeDataEvent> (_info.event_);

      switch (_msg->get_action ())
        {
        case ::libs::imdata_events::events::ChangeNodePathAction::get:
          {
            ::libs::imdata_events::events::ChangeNodeDataEvent::events_list_type _events;

            _events.push_back (::libs::iproperties::helpers::clone_event (finfo_.props_.get ()));
            _msg->set_events (_events);
            break;
          }
        case ::libs::imdata_events::events::ChangeNodePathAction::set:
          {
            auto _events = _msg->get_events ();
            bool _update = false;

            for (auto _event : _events)
              {
                if (_event->get_mid () == finfo_.props_->get_mid ())
                  {
                    finfo_.props_->copy (_event.get ());
                    _update = true;
                  }
              }

            finfo_.sync (_update);
            break;
          }
        default:
          {
            UASSERT_SIGNAL ("failed, unsupported action ChangeNodeDataEvent");
            break;
          }
        }

      return;
    };

    return;
  }
};

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
