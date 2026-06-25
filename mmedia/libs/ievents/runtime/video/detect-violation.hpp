#pragma once
/**
\file       detect-violation.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::video
{
/// Событие-уведомление о сработки детектора автивности (движение/звук/etc)
class DetectViolation : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (DetectViolation)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (DetectViolation)
  U3_HELPER_DISABLE_ACOPY_TYPE (DetectViolation)

  explicit DetectViolation (const Acessor& = Acessor (0), const DetectViolations& state = DetectViolations::start);
  virtual ~DetectViolation () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/video/detect-violation";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  void             sync_event_props (const DetectViolations&);
  void             set_state (const DetectViolations& state);
  DetectViolations get_state () const;

  protected:
  DetectViolations state_;   //< Признак того, что акивность стартовала (в противном случае это признак окончания активности)

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::video::DetectViolation);
