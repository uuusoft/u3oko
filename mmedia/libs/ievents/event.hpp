#pragma once
/**
\file       event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents
{
/// Реализация базового интерфейса всех событий системы
class Event : public ::libs::events::IEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Event)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (Event)
  U3_HELPER_DISABLE_ACOPY_TYPE (Event)

  explicit Event (const Acessor& = Acessor (0));
  virtual ~Event () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_gextp_json () const -> const std::string&;
  auto set_gextp_json (const std::string&) -> void;

  protected:
  // ::libs::events::IEvent overrides
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  std::string gextp_json_;   //< general extended properties json format

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::IEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::Event);
BOOST_CLASS_TRACKING (::libs::ievents::Event, boost::serialization::track_always);
