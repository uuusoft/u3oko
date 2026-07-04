#pragma once
/**
\file       link-impl-one-proc.hpp
\author     Erashov Anton erashov2026@proton.me
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
  using lock_type       = std::scoped_lock< sync_type >;
  using helper_ptr_type = LinkImplOneProcInt::weak_ptr;

  //  ILink overrides
  virtual auto connect_int (const ::libs::link::CreateInfo&) -> bool override;
  virtual auto listen_int (const ::libs::link::CreateInfo&) -> bool override;
  virtual auto destroy_int (const ::libs::link::LinkDestroys&) -> bool override;
  virtual auto is_connected_int () const -> bool override;
  virtual auto received_msg_int () -> syn::IEvent::ptr override;
  virtual auto get_imem_int () -> syn::IMem::raw_ptr override;
  virtual auto complite_msg_int (const syn::IEvent::ptr&, const ::libs::link::StateProcessEvent&) -> void override;
  virtual auto send_msg_int (const syn::IEvent::ptr&, const syn::CallSyncs&, const syn::Calls&, const ::libs::events::ISeqEvent::id_type&) -> syn::IEvent::ptr override;

  auto get_shared_impl () const -> LinkImplOneProcInt::ptr;

  mutable sync_type mtx_;       //< Синхронизирующий примитив для доступа к объекту EAI-REMOVE
  CreateInfoExt     info_;      //< Информация, использованная при создании объекта
  helper_ptr_type   phelper_;   //< Вспомогательная реализация. Она разделяется между двумя объектами "связь" с каждой ее стороны и имеет свой уровень синхронизации
};
}   // namespace libs::ilink::impl::oneproc
