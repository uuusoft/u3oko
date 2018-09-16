#pragma once
/**
\file       get-events-from-base.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.09.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents_events { namespace events {
/**
\brief  ѕолучить событи€ из базы.
*/
class GetEventsFromBase : public BaseEventsEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  // ext types
  using events_res_type   = std::vector<IEvent::ptr>;
  using events_types_type = std::vector<IEvent::hid_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (GetEventsFromBase);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetEventsFromBase);
  UUU_DISABLE_ACOPY_TYPE (GetEventsFromBase);

  GetEventsFromBase (const Acessor& = Acessor (0));

  virtual ~GetEventsFromBase ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents_events/events/get-events-from-base";
    return _ret;
  }

  void set_events (events_res_type& _events);

  const events_res_type& get_events () const;

  void set_types(events_types_type& _types);

  const events_types_type& get_types() const;


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent);

  events_res_type   events_;      //< —писок событий из базы, соответствующих заданным критери€м.
  events_types_type types_;       //< —писок типов событий, которые требуетс€ получить из базы. ѕустой список - все типы событий.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::GetEventsFromBase);
