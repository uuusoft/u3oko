#pragma once
/**
\file       video-histogram-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::histogram
{
struct EventBufsInfoHistogram final : public ::libs::events::buf::EventBufsInfo {
  public:
  EventBufsInfoHistogram ();

  bool         norm_;    //<
  std::int32_t dindx_;   //<

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};


class VideoHistogramProp final : virtual public ievents::Event
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
  using type2buf_type = std::vector< std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, EventBufsInfoHistogram > >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoHistogramProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoHistogramProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoHistogramProp)

  explicit VideoHistogramProp (const Acessor& = Acessor (0));
  explicit VideoHistogramProp (const ::libs::events::buf::EventBufsInfo& buf);
  virtual ~VideoHistogramProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/histogram/video-histogram-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  type2buf_type bufs2norm_;   //<

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
}   // namespace libs::ievents::props::videos::generic::histogram

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::histogram::EventBufsInfoHistogram);
BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::histogram::VideoHistogramProp);
