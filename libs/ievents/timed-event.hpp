#pragma once
/**
\file       timed-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents {
/**
  \brief  Базовый класс всех событий системы с временной меткой.
  */
class TimedEvent : public ievents::Event
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
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (TimedEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (TimedEvent);
  UUU_DISABLE_ACOPY_TYPE (TimedEvent);

  explicit TimedEvent (const Acessor& = Acessor (0));

  virtual ~TimedEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/timed-event";
    return _ret;
  }

  boost::posix_time::ptime get_time () const;


  protected:
  boost::posix_time::ptime time_;      //< ???

  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
};

}}      // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::TimedEvent);
