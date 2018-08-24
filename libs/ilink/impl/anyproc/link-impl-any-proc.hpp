#pragma once
/**
\file       link-impl-any-proc.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace anyproc {
/**
  \brief  empty brief
  */
class LinkImplAnyProc : public ::libs::link::ILink
{
  public:
  LinkImplAnyProc ();

  virtual ~LinkImplAnyProc ();


  private:
  //  int types
  using msgs_type       = boost::interprocess::message_queue;
  using ptr_msgs_type   = std::shared_ptr<msgs_type>;
  using imem_uptr_type  = std::unique_ptr<MemImplAnyProc>;
  using shared_mem_type = std::shared_ptr<managed_shared_memory>;
  using sync_type       = boost::interprocess::named_mutex;
  using guard_type      = std::lock_guard<sync_type>;
  using int_sync_type   = std::mutex;
  using int_guard_type  = std::lock_guard<int_sync_type>;

  //  ILink overrides
  virtual bool                             connect_int (const CreateInfo& _info) override;
  virtual bool                             listen_int (const CreateInfo& _info) override;
  virtual bool                             destroy_int (const TypeDestroyLink& _type) override;
  virtual bool                             is_connected_int () const override;
  virtual IEvent::ptr                      received_msg_int () override;
  virtual void                             complite_msg_int (IEvent::ptr _msg, const StateProcessEvent& _state) override;
  virtual ::libs::link::mem::IMem::raw_ptr get_imem_int () override;
  virtual IEvent::ptr                      send_msg_int (IEvent::ptr _msg, const TypeSyncCall& _sync = TypeSyncCall::async, const TypeRequestCall& _req = TypeRequestCall::set, const ISeqEvent::id_type& _id = ISeqEvent::id_type ()) override;

  void remove_names ();

  void* mem_get (const ::libs::link::mem::IBlockMem& _hmem);

  bool make_for_create ();

  bool make_for_creation ();

  CreateInfo         info_;               //< Информация, использованная для создания данного объекта.
  int_sync_type      mtx_;                //< Синхронизирующий примитив для управления доступом к объекту.
  loader::LoaderCode loader_;             //< Загрузчик кода.
  ptr_msgs_type      cmd_send_msgs_;      //< Очередь сообщения на передачи.
  ptr_msgs_type      cmd_recv_msgs_;      //< Очеред принятых сообщений.
  shared_mem_type    smem_;               //< Разделяемая память между сторонами данного канала.
  imem_uptr_type     heap_mem_;           //< Реализация распределения памяти для данного канала.
};

}}}}      // namespace libs::ilink::impl::anyproc
