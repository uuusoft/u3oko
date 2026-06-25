#pragma once
/**
\file       face-detect.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::video
{
/// Событие-уведомление о сработки детектора автивности (движение/звук/etc)
class FaceDetect : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (FaceDetect)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (FaceDetect)
  U3_HELPER_DISABLE_ACOPY_TYPE (FaceDetect)

  explicit FaceDetect (const Acessor& = Acessor (0), bool start = true);
  virtual ~FaceDetect () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/video/face-detect";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_start () const;

  protected:
  bool start_;   //< Признак того, что акивность стартовала (в противном случае это признак окончания активности)

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::video::FaceDetect);
