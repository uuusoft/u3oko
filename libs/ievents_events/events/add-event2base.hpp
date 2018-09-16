#pragma once
/**
\file       add-event2base.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.09.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents_events { namespace events {
/**
\brief  Добавить событие в базу.
*/
class AddEvent2Base : public BaseEventsEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (AddEvent2Base);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (AddEvent2Base);
  UUU_DISABLE_ACOPY_TYPE (AddEvent2Base);
  using object_id_type  = std::string;
  using machine_id_type = ::libs::helpers::utils::cuuid;

  AddEvent2Base (const Acessor& = Acessor (0), const ::libs::events::IEvent::ptr& _obj = ::libs::events::IEvent::ptr ());

  virtual ~AddEvent2Base ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents_events/events/add-event2base";
    return _ret;
  }

  void set_event (::libs::events::IEvent::ptr& _obj);

  ::libs::events::IEvent::ptr get_event () const;

  void set_object_id (const object_id_type& _id);

  const object_id_type& get_object_id () const;

  void set_machine_id (const machine_id_type& _id);

  const machine_id_type& get_machine_id () const;


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent);

  machine_id_type             machine_id_;      //< Идентификатор машины, которой принадлжеит объект данных.
  object_id_type              object_id_;       //< Индентификатор объекта, с которым связано событие.
  ::libs::events::IEvent::ptr int_;             //< Событие, которое требуется сохранить в базе.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::AddEvent2Base);
