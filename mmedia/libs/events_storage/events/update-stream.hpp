#pragma once
/**
\file       update-stream.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
class UpdateStream : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (UpdateStream)
  U3_ADD_MAKE_SHARED_THIS (UpdateStream)
  U3_ADD_DELETE_MOVE_COPY (UpdateStream)

  explicit UpdateStream (const Acessor& = Acessor (0));
  virtual ~UpdateStream () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_storage/events/update-stream";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  TypeObjectId     obj_id_;      //<
  stream_id_type   stream_id_;   //<
  StreamUpdates    action_;      //<
  StreamActions    operation_;   //<
  StreamDirections direction_;   //<
  TimeStream       time_;        //<

  protected:
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_storage::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::UpdateStream);
