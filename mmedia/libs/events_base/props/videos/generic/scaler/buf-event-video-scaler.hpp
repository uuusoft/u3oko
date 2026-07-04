#pragma once
/**
\file       buf-event-video-scaler.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::scaler
{
struct EventBufsVideoScaler final : public ::libs::events::buf::EventBufs {
  friend class boost::serialization::access;

  public:
  explicit EventBufsVideoScaler (
    const ::utils::dbufs::video::consts::offs::off_buf_type& src = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& dst = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufsVideoScaler (const ::libs::events::buf::EventBufs& buf);

  Scalers                              type_       = Scalers::nearest;   //< тип масштабирования
  std::int32_t                         koeff_pow2_ = 0;                  //< Степень двойки для режима Scalers::fixed_pow2
  ::libs::events::props::details::Rect src_rect_;                        //< Прямоугльник источника
  ::libs::events::props::details::Rect dst_rect_;                        //< Прямогульник назначения

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                 tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsVideoScaler& src);
EventBufsVideoScaler tag_invoke (::boost::json::value_to_tag< EventBufsVideoScaler >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::scaler

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::scaler::EventBufsVideoScaler);
