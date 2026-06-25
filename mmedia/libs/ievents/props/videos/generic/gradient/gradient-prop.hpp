#pragma once
/**
\file       gradient-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::gradient
{
class GradientProp final : virtual public ievents::Event
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
  using channels_type = std::list< std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, ChannelGradient > >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GradientProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GradientProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (GradientProp)

  explicit GradientProp (const Acessor& = Acessor (0));
  virtual ~GradientProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/gradient/gradient-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  channels_type channels_;   //< Список каналов преобразования

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  void load_layer_from_xml (const ::pugi::xml_named_node_iterator& node, ChannelGradient* prop);
  void load_layer (const std::string& vals, ChannelGradient* prop);

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::props::videos::generic::gradient

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::gradient::GradientProp);
