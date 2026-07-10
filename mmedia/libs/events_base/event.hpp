#pragma once
/**
\file       event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base
{
/// Реализация базового интерфейса всех событий системы
class Event : public ::libs::events::IEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (Event)
  U3_ADD_MAKE_SHARED_THIS (Event)
  U3_ADD_DELETE_MOVE_COPY (Event)

  explicit Event (const Acessor& = Acessor (0));
  virtual ~Event () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_gextp_json () const -> const std::string&;
  auto set_gextp_json (const std::string&) -> void;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  std::string gextp_json_;   //< general extended properties json format

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events::IEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_KEY (::libs::events_base::Event);
BOOST_CLASS_TRACKING (::libs::events_base::Event, boost::serialization::track_always);
