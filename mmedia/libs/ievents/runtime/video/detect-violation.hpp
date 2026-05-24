#pragma once
/**
\file       detect-violation.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  virtual ~DetectViolation ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/video/detect-violation";
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
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual void copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::video::DetectViolation);
