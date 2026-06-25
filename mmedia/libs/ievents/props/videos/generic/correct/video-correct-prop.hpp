#pragma once
/**
\file       video-correct-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::correct::consts
{
constexpr std::int32_t min = -1;
constexpr std::int32_t max = 1;
constexpr std::int32_t def = 0;
}   // namespace libs::ievents::props::videos::generic::correct::consts

namespace libs::ievents::props::videos::generic::correct
{
class VideoCorrectProp final : virtual public ievents::Event
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
  using parameter_type = std::pair< float, bool >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoCorrectProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoCorrectProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoCorrectProp)

  explicit VideoCorrectProp (const Acessor& = Acessor (0));
  virtual ~VideoCorrectProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/correct/video-correct-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  parameter_type saturation_ { consts::def, false };                               //< [-1.0, +1.0]
  parameter_type bright_ { consts::def, false };                                   //< [-1.0, +1.0]
  parameter_type contrast_ { consts::def, false };                                 //< [-1.0, +1.0]
  parameter_type sharp_ { consts::def, false };                                    //< [-1.0, +1.0]
  parameter_type hue_ { consts::def, false };                                      //< [-1.0, +1.0]
  parameter_type gamma_ { consts::def, false };                                    //< [-1.0, +1.0]
  parameter_type white_balance_ { consts::def, false };                            //< [-1.0, +1.0]
  parameter_type backlight_compensation_ { consts::def, false };                   //<
  parameter_type gain_ { consts::def, false };                                     //<
  parameter_type exposure_ { consts::def, false };                                 //<
  bool           adaptive_          = false;                                       //<
  bool           short2byte_        = true;                                        //<
  SelectorImpls  hint_correct_impl_ = ::libs::ievents::SelectorImpls::automatic;   //< "auto", "hard", "soft", etc

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual void self_correct_int () override;
};
}   // namespace libs::ievents::props::videos::generic::correct

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::correct::VideoCorrectProp);
