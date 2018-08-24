#pragma once
/**
\file       base-data-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      Объявление базового класса события модуля обработки данных.
*/

namespace libs { namespace imdata_events { namespace events {
/**
  \brief  Базовое событие для подсистемы обработки данных.
          Является меткой, с помощью которой события перенаправляются центральным модулем в модуль подсистемы обработки данных.
  */
class BaseDataEvent : public ::libs::ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseDataEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseDataEvent);

  BaseDataEvent (const Acessor& = Acessor (0));

  virtual ~BaseDataEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/imdata_events/events/base-data-event";
    return _ret;
  }

  protected:
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::BaseDataEvent);
