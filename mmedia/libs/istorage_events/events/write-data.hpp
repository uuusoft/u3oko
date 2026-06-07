#pragma once
/**
\file       write-data.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class WriteData : public BaseStorageEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (WriteData)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WriteData)
  U3_HELPER_DISABLE_ACOPY_TYPE (WriteData)

  explicit WriteData (const Acessor& = Acessor (0));
  virtual ~WriteData () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/write-data";
    return ret;
  }

  void                        set_stream_id (const stream_id_type& id);
  const stream_id_type&       get_stream_id () const;
  void                        set_msg (::libs::events::IEvent::ptr& buf);
  ::libs::events::IEvent::ptr get_msg () const;

  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  stream_id_type              stream_id_;   //<
  ::libs::events::IEvent::ptr buf_;         //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::WriteData);
