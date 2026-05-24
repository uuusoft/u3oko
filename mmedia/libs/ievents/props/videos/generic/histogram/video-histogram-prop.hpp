#pragma once
/**
\file       video-histogram-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  serialize (Archive& ar, const std::uint32_t /* file_version */);
};


class VideoHistogramProp final : public ievents::Event
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
  virtual ~VideoHistogramProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/histogram/video-histogram-prop";
    return ret;
  }

  type2buf_type bufs2norm_;   //<

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::histogram

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::histogram::EventBufsInfoHistogram);
BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::histogram::VideoHistogramProp);
