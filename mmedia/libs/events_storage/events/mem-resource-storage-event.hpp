#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
class MemResourceStorageEvent : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using id_mem_type         = std::string;
  using number_mem_buf_type = long long;

  U3_ADD_POINTERS_TO_SELF (MemResourceStorageEvent)
  U3_ADD_MAKE_SHARED_THIS (MemResourceStorageEvent)
  U3_ADD_DELETE_MOVE_COPY (MemResourceStorageEvent)

  explicit MemResourceStorageEvent (
    const Acessor&                    = Acessor (0),
    id_mem_type                id     = "",
    const number_mem_buf_type& number = 0);

  virtual ~MemResourceStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/mem-resource-storage-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_id () const -> const id_mem_type&;
  auto set_id (const id_mem_type& id) -> void;
  auto get_numder () const -> const number_mem_buf_type&;
  auto set_number (const number_mem_buf_type& number) -> void;
  auto get_request () const -> bool;
  auto set_request (bool request) -> void;

  protected:
  id_mem_type         id_;                             //< Идентификатор ресурса. Например см. ZipDataEvent::id_buf_type
  number_mem_buf_type number_;                         //< Порядковый номер ресурса
  bool                request_for_transmit_ = false;   //< Флаг требование - пометить буфер для передачи. Т.е. http клиент обязуется забрать данный буфер

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_storage::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::MemResourceStorageEvent);
