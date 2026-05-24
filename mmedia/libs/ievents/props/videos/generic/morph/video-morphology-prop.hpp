#pragma once
/**
\file       video-morphology-prop.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::morph
{
/// Свойства фильтра для реализации морфологических операций над изображением
class VideoMorphologyProp final : public ievents::Event
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
  using morph_buf_infos_type = std::vector< MorphBuffInfo >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoMorphologyProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoMorphologyProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoMorphologyProp)

  explicit VideoMorphologyProp (const Acessor& = Acessor (0));
  virtual ~VideoMorphologyProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/morph/video-morphology-prop";
    return ret;
  }

  morph_buf_infos_type diffs_;   //< Список буферов над которыми требуется провести морфологические операции

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
