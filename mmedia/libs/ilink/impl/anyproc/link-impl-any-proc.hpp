#pragma once
/**
\file       link-impl-any-proc.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::anyproc
{
class LinkImplAnyProc : public ::libs::link::ILink
{
  public:
  LinkImplAnyProc () = default;
  virtual ~LinkImplAnyProc ();

  private:
  //  internal typess
  using msgs_type       = boost::interprocess::message_queue;
  using ptr_msgs_type   = std::shared_ptr< msgs_type >;
  using imem_uptr_type  = std::unique_ptr< MemImplAnyProc >;
  using shared_mem_type = std::shared_ptr< boost::interprocess::managed_shared_memory >;
  using sync_type       = boost::interprocess::named_mutex;
  using lock_type       = std::scoped_lock< sync_type >;
  using int_sync_type   = std::mutex;
  using int_lock_type   = std::scoped_lock< int_sync_type >;

  //  ILink overrides
  virtual auto connect_int (const ::libs::link::CreateInfo&) -> bool override;
  virtual auto listen_int (const ::libs::link::CreateInfo&) -> bool override;
  virtual auto destroy_int (const ::libs::link::LinkDestroys&) noexcept -> bool override;
  virtual auto is_connected_int () const -> bool override;
  virtual auto received_msg_int () -> syn::IEvent::ptr override;
  virtual auto get_imem_int () -> syn::IMem::raw_ptr override;
  virtual auto complite_msg_int (const syn::IEvent::ptr&, const ::libs::link::StateProcessEvent&) -> void override;
  virtual auto send_msg_int (const syn::IEvent::ptr&, const syn::CallSyncs&, const syn::Calls&, const ::libs::events::ISeqEvent::id_type&) -> syn::IEvent::ptr override;

  void  remove_names ();
  void* mem_get (const ::libs::link::mem::IBlockFakeMem& hmem);
  bool  make_for_create ();
  bool  make_for_creation ();

  ::libs::link::CreateInfo info_;            //< Информация, использованная для создания данного объекта
  int_sync_type            mtx_;             //< Синхронизирующий примитив для управления доступом к объекту
  loader::LoaderCode       loader_;          //< Загрузчик кода
  ptr_msgs_type            cmd_send_msgs_;   //< Очередь сообщения на передачи
  ptr_msgs_type            cmd_recv_msgs_;   //< Очеред принятых сообщений
  shared_mem_type          smem_;            //< Разделяемая память между сторонами данного канала
  imem_uptr_type           heap_mem_;        //< Реализация распределения памяти для данного канала
};
}   // namespace libs::ilink::impl::anyproc
