#pragma once
/**
\file       video-correct-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::correct
{
class VideoCorrectProp final : public ievents::Event
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
  using correction_parameter_type = std::pair< float, bool >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoCorrectProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoCorrectProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoCorrectProp)

  explicit VideoCorrectProp (const Acessor& = Acessor (0));
  virtual ~VideoCorrectProp () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/correct/video-correct-prop";
    return ret;
  }

  correction_parameter_type saturation_;               //< [-1.0, +1.0]
  correction_parameter_type bright_;                   //< [-1.0, +1.0]
  correction_parameter_type contrast_;                 //< [-1.0, +1.0]
  correction_parameter_type sharp_;                    //< [-1.0, +1.0]
  correction_parameter_type hue_;                      //< [-1.0, +1.0]
  correction_parameter_type gamma_;                    //< [-1.0, +1.0]
  correction_parameter_type white_balance_;            //< [-1.0, +1.0]
  correction_parameter_type backlight_compensation_;   //<
  correction_parameter_type gain_;                     //<
  correction_parameter_type exposure_;                 //<
  bool                      adaptive_;                 //<
  bool                      short2byte_;               //<
  SelectorImpls             hint_correct_impl_;        //< "auto", "hard", "soft", etc


  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);


  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
  virtual void                        self_correct_int () override;
};
}   // namespace libs::ievents::props::videos::generic::correct

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::correct::VideoCorrectProp);
