#pragma once
/**
\file       ilink.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
*/

namespace libs::link
{
struct CallState {
  details::CallSyncs      sync_   = details::CallSyncs::async;
  details::Calls          req_    = details::Calls::set;
  syn::ISeqEvent::id_type seq_id_ = syn::ISeqEvent::id_type ();
};

/// Интерфейс, который должна поддерживать реализация связи между двумя модулями системы
class ILink
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (ILink)
  U3_ADD_DELETE_MOVE_COPY (ILink)

  /// подключения к удаленной точки-серверу
  auto connect (const CreateInfo&) -> bool;
  /// запуск точки-сервера
  auto listen (const CreateInfo&) -> bool;
  /// удаление связи
  auto destroy (const LinkDestroys& = LinkDestroys::soft) noexcept -> bool;
  /// возвращает true если свзязь установлена
  auto is_connected () const -> bool;
  /// получение сообщение по связи
  auto received_msg () -> ::libs::events::IEvent::ptr;
  /// посылки сообщения через связь
  /// \param[in]  msg  передаваемое сообщение
  /// \param[in]  sync тип синхронизации вызова
  /// \param[in]  req  тип сообщения с точки зрения запроса/ответа
  /// \param[in]  id   опциональный идентификатор транзакции, к которое принадлежит данное сообщение
  /// \return     указатель на ответное сообщение или empty
  auto send_msg (const syn::IEvent::ptr&, const CallState& = {}) -> ::libs::events::IEvent::ptr;
  ///
  auto complite_msg (const syn::IEvent::ptr&, const StateProcessEvent&) -> void;
  ///
  auto get_imem () -> mem::IMem::raw_ptr;

  protected:
  ILink ()          = default;
  virtual ~ILink () = default;

  //  ILink interface
  virtual auto connect_int (const CreateInfo&) -> bool                                      = 0;
  virtual auto listen_int (const CreateInfo&) -> bool                                       = 0;
  virtual auto destroy_int (const LinkDestroys&) noexcept -> bool                           = 0;
  virtual auto is_connected_int () const -> bool                                            = 0;
  virtual auto received_msg_int () -> syn::IEvent::ptr                                      = 0;
  virtual auto complite_msg_int (const syn::IEvent::ptr&, const StateProcessEvent&) -> void = 0;
  virtual auto get_imem_int () -> mem::IMem::raw_ptr                                        = 0;
  virtual auto send_msg_int (const syn::IEvent::ptr&, const CallState&) -> syn::IEvent::ptr = 0;
};
}   // namespace libs::link
