#pragma once
/**
\file       link-impl-any-proc.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::anyproc
{
class LinkImplAnyProc : public ::libs::link::ILink
{
  public:
  LinkImplAnyProc ();
  virtual ~LinkImplAnyProc ();

  private:
  //  internal typess
  using msgs_type       = boost::interprocess::message_queue;
  using ptr_msgs_type   = std::shared_ptr< msgs_type >;
  using imem_uptr_type  = std::unique_ptr< MemImplAnyProc >;
  using shared_mem_type = std::shared_ptr< boost::interprocess::managed_shared_memory >;
  using sync_type       = boost::interprocess::named_mutex;
  using lock_type       = std::lock_guard< sync_type >;
  using int_sync_type   = std::mutex;
  using int_lock_type   = std::lock_guard< int_sync_type >;

  //  ILink overrides
  virtual bool                             connect_int (const ::libs::link::CreateInfo&) override;
  virtual bool                             listen_int (const ::libs::link::CreateInfo&) override;
  virtual bool                             destroy_int (const ::libs::link::LinkDestroys&) override;
  virtual bool                             is_connected_int () const override;
  virtual ::libs::events::IEvent::ptr      received_msg_int () override;
  virtual void                             complite_msg_int (const ::libs::events::IEvent::ptr&, const ::libs::link::StateProcessEvent&) override;
  virtual ::libs::link::mem::IMem::raw_ptr get_imem_int () override;
  virtual ::libs::events::IEvent::ptr      send_msg_int (const ::libs::events::IEvent::ptr&, const ::libs::link::details::CallSyncs&, const ::libs::link::details::Calls&, const ::libs::events::ISeqEvent::id_type&) override;

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
