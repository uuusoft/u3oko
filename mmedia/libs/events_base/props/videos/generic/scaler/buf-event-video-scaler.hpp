#pragma once
/**
\file       buf-event-video-scaler.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::events_base::props::videos::generic::scaler::syn
{
using off_buf_type            = ::utils::dbufs::video::consts::offs::off_buf_type;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
}   // namespace libs::events_base::props::videos::generic::scaler::syn


namespace libs::events_base::props::videos::generic::scaler
{
struct EventBufsVideoScaler final : public ::libs::events::buf::EventBufs {
  friend class boost::serialization::access;

  public:
  explicit EventBufsVideoScaler (
    const syn::off_buf_type src = utils::dbufs::video::consts::offs::invalid,
    const syn::off_buf_type dst = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufsVideoScaler (const ::libs::events::buf::EventBufs& buf);

  Scalers                              type_ { Scalers::nearest };   //< тип масштабирования
  std::int32_t                         koeff_pow2_ { 0 };            //< Степень двойки для режима Scalers::fixed_pow2
  ::libs::events::props::details::Rect src_rect_;                    //< Прямоугльник источника
  ::libs::events::props::details::Rect dst_rect_;                    //< Прямогульник назначения

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsVideoScaler& src) -> void;
auto tag_invoke (::boost::json::value_to_tag< EventBufsVideoScaler >, const ::boost::json::value& jvs) -> EventBufsVideoScaler;
}   // namespace libs::events_base::props::videos::generic::scaler

U3_BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::scaler::EventBufsVideoScaler);
