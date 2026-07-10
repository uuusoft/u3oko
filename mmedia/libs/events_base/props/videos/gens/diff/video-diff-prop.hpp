#pragma once
/**
\file       video-diff-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::gens::diff
{
/// Свойства алгоритма вычисления разности между двумя кадрами для всего фильтра в целом
class VideoDiffProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using buf2info_type = std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, InfoBuffVideoDiffProp >;

  U3_ADD_POINTERS_TO_SELF (VideoDiffProp)
  U3_ADD_MAKE_SHARED_THIS (VideoDiffProp)
  U3_ADD_DELETE_MOVE_COPY (VideoDiffProp)

  explicit VideoDiffProp (const Acessor& = Acessor (0));
  virtual ~VideoDiffProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/videos/gens/diff/video-diff-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::list< buf2info_type > diffs_;   //< Список буферов и параметров для вычсления разностЕй

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
}   // namespace libs::events_base::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::gens::diff::VideoDiffProp);
