#pragma once
/**
\file       link-impl-one-proc-int.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
struct SyncStackState final {
  //  ext types
  using event_type = std::condition_variable;
  using sync_type  = std::mutex;
  using lock_type  = std::scoped_lock< sync_type >;

  U3_ADD_POINTERS_TO_SELF (SyncStackState)
  U3_ADD_DELETE_MOVE_COPY (SyncStackState)

  SyncStackState () = default;

  sync_type        evnt_mtx_;            //< Для синхронизации доступа к событию
  event_type       evnt_;                //< Событие синхронизации
  syn::IEvent::ptr active_msg_;          //< Событие в обработке
  std::atomic_bool complited_ = false;   //< Флаг завершенности, чтобы избежать гонки
};

/// Реализация "связь", разделяемая между двумя точками
class LinkImplOneProcInt final
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (LinkImplOneProcInt)

  LinkImplOneProcInt ();
  ~LinkImplOneProcInt () = default;

  auto connect (const CreateInfoExt&) -> bool;
  auto listen (const CreateInfoExt&) -> bool;
  auto is_connected () const -> bool;
  auto destroy (const CreateInfoExt&, const ::libs::link::LinkDestroys&) -> bool;
  auto received_msg (const CreateInfoExt&) -> syn::IEvent::ptr;
  auto send_msg (const CreateInfoExt&, syn::IEvent::ptr, const syn::CallSyncs&, const syn::Calls&, const ::libs::events::ISeqEvent::id_type&) -> syn::IEvent::ptr;
  auto complite_msg (const CreateInfoExt&, const syn::IEvent::ptr&, const ::libs::link::StateProcessEvent&) -> void;

  private:
  //  internal typess
  using event_msgs_type     = boost::lockfree::spsc_queue< syn::IEvent::ptr >;
  using sync_type           = std::mutex;
  using lock_type           = std::scoped_lock< sync_type >;
  using msg2sync_block_type = boost::unordered_flat_map< syn::IEvent::ptr, SyncStackState::raw_ptr >;

  auto wrap_msg (const syn::CallSyncs&, const syn::Calls&, const ::libs::events::ISeqEvent::id_type&, syn::IEvent::ptr) -> syn::IEvent::ptr;

  sync_type           mtx_;              //< Поле для синхронизации доступа к объекту
  loader::LoaderCode  loader_;           //< Загрузчик кода в пространство процесса
  event_msgs_type     cmd_send_msgs_;    //< Список сообщений на отправку
  event_msgs_type     cmd_recv_msgs_;    //< Список принятых сообщений на передачу загруженному коду
  std::atomic_bool    create_flag_;      //< Флаг синхронизации для уведомления другой стороны об успешности создания канала
  msg2sync_block_type wait_sync_msgs_;   //< Список синхронных сообщений, которые были отправлены и ждут результаты, точнее ждут потоки, которые отправили их
  std::atomic_int     counter_ref_;      //< Счетчик ссылок на данный объект со стороны управляющих структур
};
}   // namespace libs::ilink::impl::oneproc
