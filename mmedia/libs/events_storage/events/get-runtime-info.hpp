#pragma once
/**
\file       get-runtime-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
struct RuntimeStreamInfo {
  RuntimeStreamInfo () = default;

  void
  reset ()
  {
    stream_id_         = consts::empty_stream_id;
    count_write_bytes_ = 0;
    count_read_bytes_  = 0;
    count_errors_      = 0;
  }

  stream_id_type stream_id_         = consts::empty_stream_id;   //<
  std::uint64_t  count_write_bytes_ = 0;                         //<
  std::uint64_t  count_read_bytes_  = 0;                         //<
  std::uint64_t  count_errors_      = 0;                         //<

  private:
  friend class boost::serialization::access;

  // REFACT
  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (stream_id_);
    arh& BOOST_SERIALIZATION_NVP (count_write_bytes_);
    arh& BOOST_SERIALIZATION_NVP (count_read_bytes_);
    arh& BOOST_SERIALIZATION_NVP (count_errors_);
  }
};


class GetRuntimeInfo : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using runtime_storage_type = std::vector< RuntimeStreamInfo >;

  U3_ADD_POINTERS_TO_SELF (GetRuntimeInfo)
  U3_ADD_MAKE_SHARED_THIS (GetRuntimeInfo)
  U3_ADD_DELETE_MOVE_COPY (GetRuntimeInfo)

  explicit GetRuntimeInfo (const Acessor& = Acessor (0));
  virtual ~GetRuntimeInfo () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/get-runtime-info";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  path_id_type         path_id_;        //<
  runtime_storage_type stream_infos_;   //<

  protected:
  //  events_base::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_storage::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::GetRuntimeInfo);
