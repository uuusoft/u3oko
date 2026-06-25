#pragma once
/**
\file       video-scaler-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::scaler
{
class VideoScalerProp final : virtual public ievents::Event
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
  using bufs_type = std::vector< EventBufsInfoVideoScaler >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoScalerProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoScalerProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoScalerProp)

  explicit VideoScalerProp (const Acessor& = Acessor (0));
  virtual ~VideoScalerProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/scaler/video-scaler-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const bufs_type& get_bufs () const;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  bufs_type bufs_;   //<Пары источник-назачение для масштабирования

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::props::videos::generic::scaler

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::scaler::VideoScalerProp);
