#pragma once
/**
\file       video-est-motion-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::motion_est::consts
{
const std::pair< std::int8_t, std::int8_t > inv_vec (U3_CAST_INT8 (127), U3_CAST_INT8 (127));
}   // namespace libs::events_base::props::videos::generic::motion_est::consts


namespace libs::events_base::props::videos::generic::motion_est
{
class VideoEstMotionProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using bufs_type = std::vector< libs::events_base::props::videos::generic::motion_est::EventBufsMotionEst >;

  U3_ADD_POINTERS_TO_SELF (VideoEstMotionProp)
  U3_ADD_MAKE_SHARED_THIS (VideoEstMotionProp)
  U3_ADD_DELETE_MOVE_COPY (VideoEstMotionProp)

  explicit VideoEstMotionProp (const Acessor& = Acessor (0));
  virtual ~VideoEstMotionProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/videos/generic/motion_est/video-est-motion-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bufs_type bufs_;   //<

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp);
