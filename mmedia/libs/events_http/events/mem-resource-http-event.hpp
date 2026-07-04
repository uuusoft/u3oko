#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.04.2018
\project    u3_events_http
*/

namespace libs::events_http::events
{
class MemResourceHttpEvent : public BaseHttpEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using id_mem_type         = std::string;
  using number_mem_buf_type = std::int64_t;

  U3_ADD_POINTERS_TO_SELF (MemResourceHttpEvent)
  U3_ADD_MAKE_SHARED_THIS (MemResourceHttpEvent)
  U3_ADD_DELETE_MOVE_COPY (MemResourceHttpEvent)

  explicit MemResourceHttpEvent (const Acessor& = Acessor (0), id_mem_type id = "", const number_mem_buf_type& number = 0);
  virtual ~MemResourceHttpEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_http/events/mem-resource-http-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_id () const -> const id_mem_type&;
  auto set_id (const id_mem_type& id) -> void;
  auto get_frame_numder () const -> const number_mem_buf_type&;
  auto set_frame_number (const number_mem_buf_type& number) -> void;
  auto get_request () const -> bool;
  auto set_request (bool request) -> void;

  protected:
  id_mem_type         id_;                     //< Идентифкатор ресурса. Например см. ZipDataEvent::id_buf_type
  number_mem_buf_type number_;                 //< Порядковый номер ресурса
  bool                request_for_transmit_;   //< Флаг требование - пометить буфер для передачи. Т.е. http клиент обязуется забрать данный буфер

  private:
  U3_ADD_SUPER_CLASS (::libs::events_http::events::BaseHttpEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_http::events

BOOST_CLASS_EXPORT_KEY (::libs::events_http::events::MemResourceHttpEvent);
