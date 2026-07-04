#pragma once
/**
\file       video-time-noise-remover-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::noises::time::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;
}

namespace libs::events_base::props::videos::noises::time
{
/// Свойства фильтрации во временной области
class VideoTimeNoiseRemoverProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using source_bufs_type = std::vector< BuffVideoTimeNoiseRemoverProp >;

  U3_ADD_POINTERS_TO_SELF (VideoTimeNoiseRemoverProp)
  U3_ADD_MAKE_SHARED_THIS (VideoTimeNoiseRemoverProp)
  U3_ADD_DELETE_MOVE_COPY (VideoTimeNoiseRemoverProp)

  explicit VideoTimeNoiseRemoverProp (const Acessor& = Acessor (0));
  virtual ~VideoTimeNoiseRemoverProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/noises/time/video-time-noise-remover-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::string      name_impl_          = "median2";   //< Имя реализации, которая будет использованя для фильтрации
  std::int32_t     dump_counter_frame_ = 0;           //< Вывода времени работы через заданное количество кадров. 0 - отключение вывода (по умолчанию)
  source_bufs_type bufs_;                             //< Список буферов с настройками для фильтрации

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
  virtual void self_correct_int () override;
};
}   // namespace libs::events_base::props::videos::noises::time

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::noises::time::VideoTimeNoiseRemoverProp);
