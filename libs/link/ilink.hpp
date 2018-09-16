#pragma once
/**
\file       ilink.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link {
/**
\brief  Интерфейс, который должна поддерживать реализация связи между двумя модулями системы.
*/
class ILink
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ILink);

  ILink (const ILink& _src) = delete;
  ILink& operator= (const ILink& _src) = delete;
  /**
  \brief      Функция подключения к удаленной точки-серверу.
  \param[in]  _info параметры подключения.
  \return     true, при успехе.
  */
  bool connect (const CreateInfo& _info);
  /**
  \brief      Функция запуска точки-сервера.
  \param[in]  _info параметры подключения.
  \return     true, при успехе.
  */
  bool listen (const CreateInfo& _info);
  /**
  \brief    Функция удаление связи.
  \param[in]  _type флаг принудительного удаления.
  \return   true, при успехе.
  */
  bool destroy (const DestroyLinkType& _type = DestroyLinkType::soft);
  /**
  \brief    Функция определяет, на сколько 
  \return   true, при успехе.
  */
  bool is_connected () const;
  /**
  \brief    Функция получение сообщение по связи. 
  \return   указатель на сообщение или empty.
  */
  IEvent::ptr received_msg ();
  /**
  \brief      Функция посылки сообщения через связь.
  \param[in]  _msg  передаваемое сообщение
  \param[in]  _sync тип синхронизации вызова.
  \param[in]  _req  тип сообщения с точки зрения запроса/ответа.
  \param[in]  _id   опциональный идентификатор транзакции, к которое принадлежит данное сообщение.
  \return     указатель на ответное сообщение или empty.
  */
  IEvent::ptr send_msg (
    IEvent::ptr                     _msg,
    const details::SyncCallType&    _sync = details::SyncCallType::async,
    const details::RequestCallType& _req  = details::RequestCallType::set,
    const ISeqEvent::id_type&       _id   = ISeqEvent::id_type ());
  /**
  \brief      Функция. 
  \param[in]  _msg  
  \param[in]  _state  
  */
  void complite_msg (IEvent::ptr _msg, const StateProcessEvent& _state);
  /**
  \brief      Функция. 
  \param[in]  _msg  
  \param[in]  _state  
  */
  mem::IMem::raw_ptr get_imem ();


  protected:
  ILink ();

  virtual ~ILink ();
  //  ILink interface
  virtual bool               connect_int (const CreateInfo& _info)                                                                                                    = 0;
  virtual bool               listen_int (const CreateInfo& _info)                                                                                                     = 0;
  virtual bool               destroy_int (const DestroyLinkType& _type)                                                                                               = 0;
  virtual bool               is_connected_int () const                                                                                                                = 0;
  virtual IEvent::ptr        received_msg_int ()                                                                                                                      = 0;
  virtual void               complite_msg_int (IEvent::ptr _msg, const StateProcessEvent& _state)                                                                     = 0;
  virtual mem::IMem::raw_ptr get_imem_int ()                                                                                                                          = 0;
  virtual IEvent::ptr        send_msg_int (IEvent::ptr _msg, const details::SyncCallType& _sync, const details::RequestCallType& _req, const ISeqEvent::id_type& _id) = 0;
};

}}      // namespace libs::link
