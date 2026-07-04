#pragma once
/**
\file       video-morphology-prop.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::morph
{
/// Свойства фильтра для реализации морфологических операций над изображением
class VideoMorphologyProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using morph_buf_infos_type = std::vector< MorphBuffInfo >;

  U3_ADD_POINTERS_TO_SELF (VideoMorphologyProp)
  U3_ADD_MAKE_SHARED_THIS (VideoMorphologyProp)
  U3_ADD_DELETE_MOVE_COPY (VideoMorphologyProp)

  explicit VideoMorphologyProp (const Acessor& = Acessor (0));
  virtual ~VideoMorphologyProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/generic/morph/video-morphology-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  morph_buf_infos_type diffs_;   //< Список буферов над которыми требуется провести морфологические операции

  private:
  //  internal typess
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
}   // namespace libs::events_base::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::morph::VideoMorphologyProp);
