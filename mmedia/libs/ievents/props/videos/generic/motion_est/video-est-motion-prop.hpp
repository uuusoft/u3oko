#pragma once
/**
\file       video-est-motion-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::motion_est::consts
{
const std::pair< std::int8_t, std::int8_t > inv_vec (U3_CAST_INT8 (127), U3_CAST_INT8 (127));
}   // namespace libs::ievents::props::videos::generic::motion_est::consts


namespace libs::ievents::props::videos::generic::motion_est
{
class VideoEstMotionProp final : virtual public ievents::Event
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
  using bufs_type = std::vector< libs::ievents::props::videos::generic::motion_est::EventBufsInfoMotionEst >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoEstMotionProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoEstMotionProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoEstMotionProp)

  explicit VideoEstMotionProp (const Acessor& = Acessor (0));
  virtual ~VideoEstMotionProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/motion_est/video-est-motion-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bufs_type bufs_;   //<

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
}   // namespace libs::ievents::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp);
