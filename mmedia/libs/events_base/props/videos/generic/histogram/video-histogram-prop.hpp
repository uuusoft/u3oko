#pragma once
/**
\file       video-histogram-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::histogram
{
struct EventBufsHistogram final : public ::libs::events::buf::EventBufs {
  public:
  EventBufsHistogram () = default;

  bool         norm_  = false;   //<
  std::int32_t dindx_ = -1;      //<

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};


class VideoHistogramProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using type2buf_type = std::vector< std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, EventBufsHistogram > >;

  U3_ADD_POINTERS_TO_SELF (VideoHistogramProp)
  U3_ADD_MAKE_SHARED_THIS (VideoHistogramProp)
  U3_ADD_DELETE_MOVE_COPY (VideoHistogramProp)

  explicit VideoHistogramProp (const Acessor& = Acessor (0));
  explicit VideoHistogramProp (const ::libs::events::buf::EventBufs& buf);
  virtual ~VideoHistogramProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/generic/histogram/video-histogram-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  type2buf_type bufs2norm_;   //<

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
}   // namespace libs::events_base::props::videos::generic::histogram

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::histogram::EventBufsHistogram);
BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::histogram::VideoHistogramProp);
