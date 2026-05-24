#pragma once
/**
\file       link-impl-one-proc.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
/// Реализация интерфейса "связь" для случая работы системы в одном процессе
class LinkImplOneProc final : public ::libs::link::ILink
{
  public:
  /// Конструктор
  /// \param[in]  разделяемая между двумя сторонами реализация связи
  explicit LinkImplOneProc (LinkImplOneProcInt::weak_ptr&);
  virtual ~LinkImplOneProc ();

  private:
  //  internal typess
  using sync_type       = std::mutex;
  using lock_type       = std::lock_guard< sync_type >;
  using helper_ptr_type = LinkImplOneProcInt::weak_ptr;

  //  ILink overrides
  virtual bool                             connect_int (const ::libs::link::CreateInfo&) override;
  virtual bool                             listen_int (const ::libs::link::CreateInfo&) override;
  virtual bool                             destroy_int (const ::libs::link::LinkDestroys&) override;
  virtual bool                             is_connected_int () const override;
  virtual ::libs::events::IEvent::ptr      received_msg_int () override;
  virtual ::libs::link::mem::IMem::raw_ptr get_imem_int () override;
  virtual void                             complite_msg_int (const ::libs::events::IEvent::ptr&, const ::libs::link::StateProcessEvent&) override;
  virtual ::libs::events::IEvent::ptr      send_msg_int (const ::libs::events::IEvent::ptr&, const ::libs::link::details::CallSyncs&, const ::libs::link::details::Calls&, const ::libs::events::ISeqEvent::id_type&) override;
  LinkImplOneProcInt::ptr                  get_shared_impl () const;

  mutable sync_type mtx_;       //< Синхронизирующий примитив для доступа к объекту EAI-REMOVE
  CreateInfoExt     info_;      //< Информация, использованная при создании объекта
  helper_ptr_type   phelper_;   //< Вспомогательная реализация. Она разделяется между двумя объектами "связь" с каждой ее стороны и имеет свой уровень синхронизации
};
}   // namespace libs::ilink::impl::oneproc
