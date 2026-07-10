#pragma once
/**
\file       face-detect.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::video
{
/// Событие-уведомление о сработки детектора автивности (движение/звук/etc)
class FaceDetect : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (FaceDetect)
  U3_ADD_MAKE_SHARED_THIS (FaceDetect)
  U3_ADD_DELETE_MOVE_COPY (FaceDetect)

  explicit FaceDetect (const Acessor& = Acessor (0), bool start = true);
  virtual ~FaceDetect () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/runtime/video/face-detect";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_start () const;

  protected:
  bool start_;   //< Признак того, что акивность стартовала (в противном случае это признак окончания активности)

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::video::FaceDetect);
