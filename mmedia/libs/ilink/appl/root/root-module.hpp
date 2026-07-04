#pragma once
/**
\file       root-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::appl::root::consts
{
inline constexpr std::uint32_t minute_period_dump_state = 1;
}

namespace libs::ilink::appl::root
{
/// Базовый тип для реализации модуля-приложения. Обеспечивает маршрутизацию событий между модулями-листками
class RootModule : public base::BaseModule
{
  public:
  RootModule ();
  virtual ~RootModule () = default;

  protected:
  //  internal typess
  using compare_process_type = std::function< bool (const StateProcessEventExt&, const StateProcessEventExt&) >;   //<
  using seq2process_type     = std::set< StateProcessEventExt, compare_process_type >;                             //< U3-REFACT to unordered_set

  //  base::BaseModule impl
  virtual auto init_links_int (const ::libs::link::appl::InitApplication&) -> void override;
  virtual auto init_proxys_int () -> void override;
  virtual auto appl_work_int () -> void override;
  virtual auto appl_deinit_int () -> bool override;
  virtual auto update_catch_funcs_int () -> void override;

  seq2process_type seqs_;   //< Запросы в процессе обработки

  private:
  // internal types
  using time_type     = boost::posix_time::ptime;
  using duration_type = boost::posix_time::time_duration;

  U3_ADD_SUPER_CLASS (::libs::ilink::appl::base::BaseModule)

  /// Функция возвращает по сообщению связь к модулю, который будет его обрабатывать
  /// Или пусто, если обработка должа производится в текущем модуле
  /// \param[in]  msg  сообщение
  /// \return     связь к модулю или пусто, если модуль неизвестен
  auto get_dest_link (syn::IEvent::ptr& msg) -> ::libs::link::ILink::ptr;

  DeInitStages  deinit_stage_         = DeInitStages::send_stop_msg2allmost_all;                //< Текущая стадия становки модуля
  std::uint64_t deinit_stage_counter_ = 0;                                                      //<
  time_type     time_dump_status_     = boost::posix_time::microsec_clock::universal_time ();   //< Время последнего вывода информации о статусе системы в лог
};
}   // namespace libs::ilink::appl::root
