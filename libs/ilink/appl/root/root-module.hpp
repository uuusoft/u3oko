#pragma once
/**
\file       root-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace appl { namespace root {
//  syn
using ::libs::link::details::RunCodeType;
using ::libs::link::appl::InitApplication;
using ::libs::iproperties::appl_paths::TypePath;
using ::libs::events::ISeqEvent;
using ::libs::helpers::sys::cpu::TextExtCpu;
/**
\brief  Базовый тип для реализации модуля-приложения. 
        Обеспечивает маршрутизацию событий между модулями-листками.
*/
class RootModule : public base::BaseModule
{
  public:
  RootModule ();

  virtual ~RootModule ();


  protected:
  //  int types
  using compare_process_type = std::function<bool(const StateProcessEventExt& _left, const StateProcessEventExt& _right)>;
  using seq2process_type     = std::set<StateProcessEventExt, compare_process_type>;

  //  base::BaseModule impl
  virtual void init_links_int (const InitApplication& _info) override;
  virtual void init_proxys_int () override;
  virtual void work_int () override;
  virtual bool deinit_int () override;
  virtual void update_catch_functs_int () override;

  seq2process_type seqs_;              //< Запросы в процессе обработки.
  TypeStageDeInit  deinit_stage_;      //< Текущая стадия становки модуля.


  private:
  // int types
  using time_type     = boost::posix_time::ptime;
  using duration_type = boost::posix_time::time_duration;
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::base::BaseModule);
  /**
  \brief      Функция обработчик сообщения по умолчанию.
  \param[in]  _msg  исходное сообщение.
  \return     следующее связанное с исходным сообщение или пусто.
  */
  IEvent::ptr default_catch_funct (IEvent::ptr _msg, bool _forward);
  /**
  \brief      Функция обработчик сообщения признака синхронности.
  \param[in]  _msg  исходное сообщение.
  \return     следующее связанное с исходным сообщение или пусто.
  */
  IEvent::ptr sync_msg_catch_funct (IEvent::ptr _msg, bool _forward);
  /**
  \brief      Функция обработчик сообщения признака запроса.
  \param[in]  _msg  исходное сообщение.
  \return     следующее связанное с исходным сообщение или пусто.
  */
  IEvent::ptr request_msg_catch_funct (IEvent::ptr _msg, bool _forward);
  /**
  \brief      Функция обработчик сообщения признака ответа на запрос.
  \param[in]  _msg  исходное сообщение.
  \return     следующее связанное с исходным сообщение или пусто.
  */
  IEvent::ptr answer_msg_catch_funct (IEvent::ptr _msg, bool _forward);
  /**
  \brief      Функция обработчик сообщения транзакции.
  \param[in]  _msg  исходное сообщение.
  \return     следующее связанное с исходным сообщение или пусто.
  */
  IEvent::ptr seq_msg_catch_funct (IEvent::ptr _msg, bool _forward);
  /**
  \brief      Функция возвращает по сообщению связь к модулю, который будет его обрабатывать. 
              Или пусто, если обработка должа производится в текущем модуле.
  \param[in]  _msg  сообщение.
  \return     связь к модулю или пусто, если модуль неизвестен.
  */
  ILink::ptr get_dest_link (IEvent::ptr _msg);

  time_type last_time_dump_status_system_;      //< Время последнего вывода информации о статусе системы в лог.
};

}}}}      // namespace libs::ilink::appl::root
