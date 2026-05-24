#pragma once
/**
\file       root-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::appl::root::consts
{
constexpr std::uint32_t minute_period_dump_state = 1;
}

namespace libs::ilink::appl::root
{
/// Базовый тип для реализации модуля-приложения. Обеспечивает маршрутизацию событий между модулями-листками
class RootModule : public base::BaseModule
{
  public:
  RootModule ();
  virtual ~RootModule ();

  protected:
  //  internal typess
  using compare_process_type = std::function< bool (const StateProcessEventExt&, const StateProcessEventExt&) >;   //<
  using seq2process_type     = std::set< StateProcessEventExt, compare_process_type >;                             //< U3-REFACT to unordered_set

  //  base::BaseModule impl
  virtual void init_links_int (const ::libs::link::appl::InitApplication&) override;
  virtual void init_proxys_int () override;
  virtual void appl_work_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  seq2process_type seqs_;   //< Запросы в процессе обработки

  private:
  // internal types
  using time_type     = boost::posix_time::ptime;
  using duration_type = boost::posix_time::time_duration;

  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::base::BaseModule)

  /// Функция обработчик сообщения по умолчанию
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  syn::IEvent::ptr default_catch_func (syn::IEvent::ptr&, bool forward, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака синхронности
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  syn::IEvent::ptr sync_msg_catch_func (syn::IEvent::ptr&, bool forward, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака запроса
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  syn::IEvent::ptr request_msg_catch_func (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt&);

  /// Функция обработчик сообщения признака ответа на запрос
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  syn::IEvent::ptr answer_msg_catch_func (syn::IEvent::ptr&, bool forward, const StateProcessEventExt&);

  /// Функция обработчик сообщения транзакции
  /// \param[in]  msg  исходное сообщение
  /// \return     следующее связанное с исходным сообщение или пусто
  syn::IEvent::ptr seq_msg_catch_func (syn::IEvent::ptr&, bool forward, const StateProcessEventExt&);

  /// Функция возвращает по сообщению связь к модулю, который будет его обрабатывать
  /// Или пусто, если обработка должа производится в текущем модуле
  /// \param[in]  msg  сообщение
  /// \return     связь к модулю или пусто, если модуль неизвестен
  ::libs::link::ILink::ptr get_dest_link (syn::IEvent::ptr& msg);

  DeInitStages  deinit_stage_;           //< Текущая стадия становки модуля
  std::uint64_t deinit_stage_counter_;   //<
  time_type     time_dump_status_;       //< Время последнего вывода информации о статусе системы в лог
};
}   // namespace libs::ilink::appl::root
