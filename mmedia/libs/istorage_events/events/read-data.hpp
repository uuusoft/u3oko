#pragma once
/**
\file       read-data.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class ReadData : public BaseStorageEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ReadData)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ReadData)
  U3_HELPER_DISABLE_ACOPY_TYPE (ReadData)

  explicit ReadData (const Acessor& = Acessor (0));
  virtual ~ReadData () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/istorage_events/events/read-data";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_stream_id (const stream_id_type& id) -> void;
  auto get_stream_id () const -> const stream_id_type&;
  auto set_msg (::libs::events::IEvent::ptr& buf) -> void;
  auto get_msg () const -> ::libs::events::IEvent::ptr;

  protected:
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  stream_id_type              stream_id_;   //<
  ::libs::events::IEvent::ptr buf_;         //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::ReadData);
