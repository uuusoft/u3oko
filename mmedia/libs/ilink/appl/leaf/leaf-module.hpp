#pragma once
/**
\file       leaf-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::appl::leaf
{
/// Базовая реализация для всех типов модулей (корневых оконечных etc) системы
class LeafModule : public ::libs::ilink::appl::base::BaseModule
{
  public:
  LeafModule ();
  virtual ~LeafModule ();

  protected:
  //  ::libs::ilink::appl::base::BaseModule impl
  virtual void appl_work_int () override;
  virtual void update_catch_funcs_int () override;

  /// Функция обработки сообщения
  /// \param[in]  evnt сообщение
  /// \return     true, если нужно продолжить работу цикла выборки сообщений, или false
  virtual bool catch_event (::libs::events::IEvent::ptr& evnt) = 0;

  /// Функция решения, нужно ли засыпать в рабочем потоке после обработки текущего сообщения
  /// \param[in]  now_recv_evnt  флаг, сообщение было получено
  /// \return     true, если нужно заснуть в рабочем потоке на некоторое время
  virtual bool is_now_thread_to_sleep (bool now_recv_evnt) = 0;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::base::BaseModule)

  /// Функция обработчик сообщения по умолчанию
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  ::libs::events::IEvent::ptr default_catch_func (syn::IEvent::ptr&, bool, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака синхронности
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  ::libs::events::IEvent::ptr sync_msg_catch_func (syn::IEvent::ptr&, bool, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака запроса
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  ::libs::events::IEvent::ptr request_msg_catch_func (syn::IEvent::ptr&, bool, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака ответа на запрос
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  ::libs::events::IEvent::ptr answer_msg_catch_func (syn::IEvent::ptr&, bool, const StateProcessEventExt&);

  /// Функция обработчик сообщения транзакции
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  ::libs::events::IEvent::ptr seq_msg_catch_func (syn::IEvent::ptr&, bool, const StateProcessEventExt&);
};
}   // namespace libs::ilink::appl::leaf
