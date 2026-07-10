#pragma once
/**
\file       get-statistic-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
class GetStatisticInfo : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (GetStatisticInfo)
  U3_ADD_MAKE_SHARED_THIS (GetStatisticInfo)
  U3_ADD_DELETE_MOVE_COPY (GetStatisticInfo)

  explicit GetStatisticInfo (const Acessor& = Acessor (0));
  virtual ~GetStatisticInfo () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/get-statistic-info";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::int64_t use_size_ = 0;   //<

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

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::GetStatisticInfo);
