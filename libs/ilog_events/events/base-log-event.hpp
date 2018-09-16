#pragma once
/**
\file       base-log-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/

namespace libs { namespace ilog_events { namespace events {
//  forward;
struct RegisterHelper;
/**
\brief  Базовое сообщение для подсистемы логирования. 
        Расширяет интерфейс сообщения для нужд подсистемы логирования.
*/
class BaseLogEvent : public ::libs::ievents::TimedEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseLogEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseLogEvent);

  explicit BaseLogEvent (const Acessor& = Acessor (0));

  virtual ~BaseLogEvent ();

  virtual std::string text (const TypeLogText& _type) const;


  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr _src) override;

  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent);

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::BaseLogEvent);
