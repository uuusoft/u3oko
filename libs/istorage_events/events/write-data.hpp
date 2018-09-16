#pragma once
/**
\file       write-data.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
\brief  Событие чтения/записи по идентификатору хендла и идентификатору пути.
*/
class WriteData : public BaseStorageEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (WriteData);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WriteData);
  UUU_DISABLE_ACOPY_TYPE (WriteData);

  explicit WriteData (const Acessor& = Acessor (0));

  virtual ~WriteData ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/istorage_events/events/write-data";
    return _ret;
  }

  void set_stream_id (const stream_id_type& _id);

  const stream_id_type& get_stream_id () const;

  void set_msg (::libs::events::IEvent::ptr& _buff);

  ::libs::events::IEvent::ptr get_msg () const;


  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseStorageEvent);

  stream_id_type              stream_id_;      //< Идентификатор потока.
  ::libs::events::IEvent::ptr buff_;           //< Буфер с данными . Для примера ievents::runtime::mem::BuffEvent или ievents::runtime::mem::ZipDataEvent

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::WriteData);
