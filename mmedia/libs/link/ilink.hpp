#pragma once
/**
\file       ilink.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
*/

namespace libs::link
{
/// Интерфейс, который должна поддерживать реализация связи между двумя модулями системы
class ILink
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ILink)

  ILink (const ILink& src)                = delete;
  ILink& operator= (const ILink& src)     = delete;
  ILink (ILink&& src) noexcept            = delete;
  ILink& operator= (ILink&& src) noexcept = delete;

  /// Функция подключения к удаленной точки-серверу
  bool connect (const CreateInfo& info);

  /// Функция запуска точки-сервера
  bool listen (const CreateInfo& info);

  /// Функция удаление связи
  bool destroy (const LinkDestroys& type = LinkDestroys::soft);

  /// Функция возвращает true если свзязь установлена
  bool is_connected () const;

  /// Функция получение сообщение по связи
  ::libs::events::IEvent::ptr received_msg ();

  /// Функция посылки сообщения через связь
  /// \param[in]  msg  передаваемое сообщение
  /// \param[in]  sync тип синхронизации вызова
  /// \param[in]  req  тип сообщения с точки зрения запроса/ответа
  /// \param[in]  id   опциональный идентификатор транзакции, к которое принадлежит данное сообщение
  /// \return     указатель на ответное сообщение или empty
  ::libs::events::IEvent::ptr send_msg (
    const syn::IEvent::ptr&        msg,
    const details::CallSyncs&      sync,
    const details::Calls&          req,
    const syn::ISeqEvent::id_type& id = syn::ISeqEvent::id_type ());

  void               complite_msg (const syn::IEvent::ptr&, const StateProcessEvent&);
  mem::IMem::raw_ptr get_imem ();

  protected:
  ILink ()          = default;
  virtual ~ILink () = default;

  //  ILink interface
  virtual auto connect_int (const CreateInfo&) -> bool                                                                                                      = 0;
  virtual auto listen_int (const CreateInfo&) -> bool                                                                                                       = 0;
  virtual auto destroy_int (const LinkDestroys&) -> bool                                                                                                    = 0;
  virtual auto is_connected_int () const -> bool                                                                                                            = 0;
  virtual auto received_msg_int () -> syn::IEvent::ptr                                                                                                      = 0;
  virtual auto complite_msg_int (const syn::IEvent::ptr&, const StateProcessEvent&) -> void                                                                 = 0;
  virtual auto get_imem_int () -> mem::IMem::raw_ptr                                                                                                        = 0;
  virtual auto send_msg_int (const syn::IEvent::ptr&, const details::CallSyncs&, const details::Calls&, const syn::ISeqEvent::id_type&) -> syn::IEvent::ptr = 0;
};
}   // namespace libs::link
