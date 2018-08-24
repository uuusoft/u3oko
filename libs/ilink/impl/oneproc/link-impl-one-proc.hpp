#pragma once
/**
\file       link-impl-one-proc.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace oneproc {
/**
  \brief  Реализация интерфейса "связь" для случая работы системы в одном процессе.
  */
class LinkImplOneProc : public ::libs::link::ILink
{
  public:
  /**
    \brief      Конструктор.
    \param[in]  _phelper  разделяемая между двумя сторонами реализация связи.
    */
  explicit LinkImplOneProc (LinkImplOneProcInt::weak_ptr& _phelper);

  virtual ~LinkImplOneProc ();


  private:
  //  int types
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;

  //  ILink override
  virtual bool                             connect_int (const CreateInfo& _info) override;
  virtual bool                             listen_int (const CreateInfo& _info) override;
  virtual bool                             destroy_int (const TypeDestroyLink& _type) override;
  virtual bool                             is_connected_int () const override;
  virtual IEvent::ptr                      received_msg_int () override;
  virtual ::libs::link::mem::IMem::raw_ptr get_imem_int () override;
  virtual void                             complite_msg_int (IEvent::ptr _msg, const StateProcessEvent& _state) override;
  virtual IEvent::ptr                      send_msg_int (IEvent::ptr _msg, const TypeSyncCall& _sync, const TypeRequestCall& _req, const ISeqEvent::id_type& _id) override;

  LinkImplOneProcInt::ptr get_shared_impl () const;

  mutable sync_type            mtx_;          //< Синхронизирующий примитив для доступа к объекту.
  CreateInfoExt                info_;         //< Информация, использованная при создании объекта.
  LinkImplOneProcInt::weak_ptr phelper_;      //< Вспомогательная реализация. Она разделяется между двумя объектами "связь" с каждой ее стороны и имеет свой уровень синхронизации.
};

}}}}      // namespace libs::ilink::impl::oneproc
