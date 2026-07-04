#pragma once
/**
\file       leaf-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::appl::leaf
{
/// Базовая реализация для всех типов модулей (корневых оконечных etc) системы
class LeafModule : public ::libs::ilink::appl::base::BaseModule
{
  public:
  LeafModule ()          = default;
  virtual ~LeafModule () = default;

  protected:
  //  ::libs::ilink::appl::base::BaseModule impl
  virtual auto appl_work_int () -> void override;
  virtual auto update_catch_funcs_int () -> void override;

  /// Функция обработки сообщения
  /// \param[in]  evnt сообщение
  /// \return     true, если нужно продолжить работу цикла выборки сообщений, или false
  auto catch_event (::libs::events::IEvent::ptr& evnt) -> bool;

  /// Функция решения, нужно ли засыпать в рабочем потоке после обработки текущего сообщения
  /// \param[in]  now_recv_evnt  флаг, сообщение было получено
  /// \return     true, если нужно заснуть в рабочем потоке на некоторое время
  auto is_now_thread_to_sleep (bool now_recv_evnt) -> bool;

  private:
  U3_ADD_SUPER_CLASS (::libs::ilink::appl::base::BaseModule)

  virtual auto catch_event_int (::libs::events::IEvent::ptr& evnt) -> bool = 0;
  virtual auto is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool     = 0;
};
}   // namespace libs::ilink::appl::leaf
