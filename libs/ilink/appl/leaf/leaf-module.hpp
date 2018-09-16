#pragma once
/**
\file       leaf-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace appl { namespace leaf {
/**
\brief  Базовая реализация для всех типов модулей (корневых оконечных и т.п.) системы.
*/
class LeafModule : public ::libs::ilink::appl::base::BaseModule
{
  public:
  LeafModule ();

  virtual ~LeafModule ();


  protected:
  //  ::libs::ilink::appl::base::BaseModule impl
  virtual void work_int () override;
  virtual void update_catch_functs_int () override;
  /**
  \brief      Функция обработки сообщения.
  \param[in]  _evnt сообщение.
  \return     true, если нужно продолжить работу цикла выборки сообщений, или false.
  */
  virtual bool catch_event (IEvent::ptr _evnt) = 0;
  /**
  \brief      Функция решения, нужно ли засыпать в рабочем потоке после обработки текущего сообщения.
  \param[in]  _now_recv_evnt  флаг, сообщение было получено.
  \return     true, если нужно заснуть в рабочем потоке на некоторое время.
  */
  virtual bool is_now_sleep_thread (bool _now_recv_evnt) = 0;


  private:
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
};

}}}}      // namespace libs::ilink::appl::leaf
