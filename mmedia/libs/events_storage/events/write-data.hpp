#pragma once
/**
\file       write-data.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
class WriteData : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (WriteData)
  U3_ADD_MAKE_SHARED_THIS (WriteData)
  U3_ADD_DELETE_MOVE_COPY (WriteData)

  explicit WriteData (const Acessor& = Acessor (0));
  virtual ~WriteData () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/write-data";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_stream_id (const stream_id_type& id) -> void;
  auto get_stream_id () const -> const stream_id_type&;
  auto set_msg (::libs::events::IEvent::ptr& buf) -> void;
  auto get_msg () const -> ::libs::events::IEvent::ptr;

  protected:
  //  events_base::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_storage::events::BaseStorageEvent)

  stream_id_type              stream_id_;   //<
  ::libs::events::IEvent::ptr buf_;         //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::WriteData);
