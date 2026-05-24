#pragma once
/**
\file       link-impl-one-proc-int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
struct TSyncStack final {
  //  ext types
  using event_type = std::condition_variable;
  using sync_type  = std::mutex;
  using lock_type  = std::lock_guard< sync_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (TSyncStack)
  U3_HELPER_DISABLE_ACOPY_TYPE (TSyncStack)

  TSyncStack () :
    allready_complite_ (false)
  {
  }

  sync_type                   mtx_;                         //< Для синхронизации доступа к событию
  event_type                  evnt_;                        //< Событие синхронизации
  ::libs::events::IEvent::ptr msg_in_progress_;             //< Событие в обработке
  bool                        allready_complite_ = false;   //< Флаг завершенности, чтобы избежать гонки
};

/// Реализация "связь", разделяемая между двумя точками
class LinkImplOneProcInt final
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (LinkImplOneProcInt)

  LinkImplOneProcInt ();
  ~LinkImplOneProcInt ();

  bool                        connect (const CreateInfoExt&);
  bool                        listen (const CreateInfoExt&);
  bool                        is_connected () const;
  bool                        destroy (const CreateInfoExt&, const ::libs::link::LinkDestroys&);
  ::libs::events::IEvent::ptr received_msg (const CreateInfoExt&);
  ::libs::events::IEvent::ptr send_msg (const CreateInfoExt&, ::libs::events::IEvent::ptr, const ::libs::link::details::CallSyncs&, const ::libs::link::details::Calls&, const ::libs::events::ISeqEvent::id_type&);
  void                        complite_msg (const CreateInfoExt&, ::libs::events::IEvent::ptr, const ::libs::link::StateProcessEvent&);

  private:
  //  internal typess
  using list_events_type         = std::list< ::libs::events::IEvent::ptr >;
  using sync_type                = std::mutex;
  using lock_type                = std::lock_guard< sync_type >;
  using sync_msg2sync_block_type = std::unordered_map< ::libs::events::IEvent::ptr, TSyncStack::raw_ptr >;

  sync_type                mtx_;              //< Поле для синхронизации доступа к объекту
  loader::LoaderCode       loader_;           //< Загрузчик кода в пространство процесса
  list_events_type         cmd_send_msgs_;    //< Список сообщений на отправку
  list_events_type         cmd_recv_msgs_;    //< Список принятых сообщений на передачу загруженному коду
  std::atomic_bool         create_flag_;      //< Флаг синхронизации для уведомления другой стороны об успешности создания канала
  sync_msg2sync_block_type wait_sync_msgs_;   //< Список синхронных сообщений, которые были отправлены и ждут результаты. Точнее ждут потоки, которые отправили их
  std::atomic_int          counter_ref_;      //< Счетчик ссылок на данный объект со стороны управляющих структур
};
}   // namespace libs::ilink::impl::oneproc
