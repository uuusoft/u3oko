#pragma once
/**
\file       link-impl-one-proc-int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace oneproc {
/**
  \brief  
  */
struct TSyncStack
{
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (TSyncStack);
  using event_type = std::condition_variable;
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;

  TSyncStack ()
  {}

  IEvent::ptr msg_;       //< ???
  event_type  evnt_;      //< ???
  sync_type   mtx_;       //< ???
};
/**
  \brief  Реализация "связь", разделяемая между двумя точками ее окончаний.
  */
class LinkImplOneProcInt
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (LinkImplOneProcInt);

  LinkImplOneProcInt ();

  ~LinkImplOneProcInt ();

  bool connect (const CreateInfoExt& _info);

  bool listen (const CreateInfoExt& _info);

  bool is_connected () const;

  bool destroy (const CreateInfoExt& _info, const TypeDestroyLink& _type);

  IEvent::ptr received_msg (const CreateInfoExt& _info);

  IEvent::ptr send_msg (
    const CreateInfoExt&      _info,
    IEvent::ptr               _msg,
    const TypeSyncCall&       _sync,
    const TypeRequestCall&    _req,
    const ISeqEvent::id_type& _id);

  void complite_msg (const CreateInfoExt& _info, IEvent::ptr _msg, const StateProcessEvent& _state);


  private:
  //  int types
  using list_events_type         = std::list<IEvent::ptr>;
  using sync_type                = std::mutex;
  using guard_type               = std::lock_guard<sync_type>;
  using sync_msg2sync_block_type = std::map<IEvent::ptr, TSyncStack::raw_ptr>;

  sync_type                mtx_;                 //< Поле для синхронизации доступа к объекту.
  loader::LoaderCode       loader_;              //< Загрузчик кода в пространство процесса.
  list_events_type         cmd_send_msgs_;       //< Список сообщений на отправку.
  list_events_type         cmd_recv_msgs_;       //< Список принятых сообщений на передачу загруженному коду.
  std::atomic_bool         create_flag_;         //< Флаг синхронизации для уведомления другой стороны об успешности создания канала.
  sync_msg2sync_block_type wait_sync_msgs_;      //< Список синхронных сообщений, которые были отправлены и ждут результаты. Точнее ждут потоки, которые отправили их.
  std::atomic_int          counter_ref_;         //< Счетчик ссылок на данный объект со стороны управляющих структур.
};

}}}}      // namespace libs::ilink::impl::oneproc
