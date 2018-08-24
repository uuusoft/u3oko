#pragma once
/**
\file       events-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2017
\copyright  www.uuusoft.com
\project    uuu_devents
\brief      empty brief
*/

namespace dlls { namespace devents { namespace impl {
/**
  \brief  Реализация управлением событиями в системе.
  */
class EventsImpl : public ::libs::events::io::IEvents
{
  public:
  //  ext types
  using create_event_funct_type = std::function<IEvent::ptr ()>;
  using str2gen_events_type     = std::unordered_map<text_id_type, create_event_funct_type>;
  using cast_event_funct_type   = std::function<IEvent::craw_ptr (IEvent::craw_ptr)>;
  using str2cast_events_type    = std::unordered_map<text_id_type, cast_event_funct_type>;
  using sync_type               = std::mutex;
  using guard_type              = std::lock_guard<sync_type>;

  EventsImpl ();

  virtual ~EventsImpl ();

  virtual IEvent::ptr get (const text_id_type& _id) override;
  virtual IEvent::ptr clone (const IEvent::craw_ptr _src, const ::libs::events::TypeCloneEvent& _type) override;
  virtual void*       dcast (IEvent::craw_ptr _src, const text_id_type& _id) override;
  virtual bool        event2xml (IEvent::ptr& _src, std::string& _xml) override;
  virtual bool        xml2event (const std::string& _xml, IEvent::ptr& _dst) override;


  private:
  void construct ();

  str2gen_events_type  gen_funct_events_;       //< Функции для создания событий по их идентификаторам.
  str2cast_events_type cast_funct_events_;      //< Функции преобразования событий.
  sync_type            mtx_;                    //< Синхронизирущий примитив.
};

}}}      // namespace dlls::devents::impl
