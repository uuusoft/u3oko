#pragma once
/**
\file       update-stream.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class UpdateStream : public BaseStorageEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (UpdateStream)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (UpdateStream)
  U3_HELPER_DISABLE_ACOPY_TYPE (UpdateStream)

  explicit UpdateStream (const Acessor& = Acessor (0));
  virtual ~UpdateStream ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/update-stream";
    return ret;
  }

  TypeObjectId     obj_id_;      //<
  stream_id_type   stream_id_;   //<
  StreamUpdates    action_;      //<
  StreamActions    operation_;   //<
  StreamDirections direction_;   //<
  TimeStream       time_;        //<

  protected:
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::UpdateStream);
