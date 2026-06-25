#pragma once
/**
\file       system-specific-driver-prop.hpp
\date       08.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::video
{
class SystemSpecificDriverProp final : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SystemSpecificDriverProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (SystemSpecificDriverProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (SystemSpecificDriverProp)

  explicit SystemSpecificDriverProp (const Acessor& = Acessor (0));
  virtual ~SystemSpecificDriverProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/video/system-specific-driver-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool show_system_page_;   //<

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::video::SystemSpecificDriverProp);
