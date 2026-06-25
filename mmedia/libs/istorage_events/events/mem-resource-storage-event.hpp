#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class MemResourceStorageEvent : public BaseStorageEvent
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
  using id_mem_type         = std::string;
  using number_mem_buf_type = long long;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MemResourceStorageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MemResourceStorageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (MemResourceStorageEvent)

  explicit MemResourceStorageEvent (
    const Acessor&                    = Acessor (0),
    const id_mem_type&         id     = "",
    const number_mem_buf_type& number = 0);

  virtual ~MemResourceStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/istorage_events/events/mem-resource-storage-event";
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
  id_mem_type         id_;                     //< Идентификатор ресурса. Например см. ZipDataEvent::id_buf_type
  number_mem_buf_type number_;                 //< Порядковый номер ресурса
  bool                request_for_transmit_;   //< Флаг требование - пометить буфер для передачи. Т.е. http клиент обязуется забрать данный буфер

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::MemResourceStorageEvent);
