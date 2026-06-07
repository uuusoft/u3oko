#pragma once
/**
\file       vec2image-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::vec2image
{
class Vec2ImageProp final : public ::libs::ievents::Event
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
  using vec_bufs_type = std::vector< EventBufsInfoVec2Image1 >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Vec2ImageProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (Vec2ImageProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (Vec2ImageProp)

  explicit Vec2ImageProp (
    const Acessor&            = Acessor (0),
    const vec_bufs_type& bufs = { EventBufsInfoVec2Image1 (::utils::dbufs::video::consts::offs::temp1, ::utils::dbufs::video::consts::offs::lit) });

  virtual ~Vec2ImageProp () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/vec2image/vec2image-prop";
    return ret;
  }

  vec_bufs_type bufs_;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp);
