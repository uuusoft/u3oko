#pragma once
/**
\file       except-log-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/

namespace libs { namespace ilog_events { namespace events {
/**
\brief  empty brief
*/
class ExceptLogEvent : public InfoLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ExceptLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ExceptLogEvent);
  UUU_DISABLE_ACOPY_TYPE (ExceptLogEvent);

  explicit ExceptLogEvent (
    const Acessor&                = Acessor (0),
    const AppllPartLogInfo& _appl = AppllPartLogInfo ("xxx", __FILE__, __LINE__),
    const std::string&      _info = "???");

  virtual ~ExceptLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ilog_events/events/except-log-event";
    return _ret;
  }


  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (InfoLogEvent);

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ExceptLogEvent);
