/**
\file       buf-event-video-scaler.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "buf-event-video-scaler.hpp"

namespace libs::events_base::props::videos::generic::scaler
{
EventBufsVideoScaler::EventBufsVideoScaler (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst) :
  ::libs::events::buf::EventBufs (src, dst)
{
}


EventBufsVideoScaler::EventBufsVideoScaler (const ::libs::events::buf::EventBufs& buf) :
  ::libs::events::buf::EventBufs (buf)
{
}


template< class Archive >
void
EventBufsVideoScaler::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoeventsobufoEventBufs", super);
  arh& BOOST_SERIALIZATION_NVP (type_);
  arh& BOOST_SERIALIZATION_NVP (src_rect_);
  arh& BOOST_SERIALIZATION_NVP (dst_rect_);
  arh& BOOST_SERIALIZATION_NVP (koeff_pow2_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const EventBufsVideoScaler& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::utility::casts::static_cast_helper< const ::libs::events::buf::EventBufs& > (src));

  jvs = {
    { "parent", pjv },
    { "type", ::boost::json::value_from (src.type_) },
    { "koeff_pow2", src.koeff_pow2_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< EventBufsVideoScaler >, const ::boost::json::value& jvs) -> EventBufsVideoScaler
{
  const auto&          pobj = jvs.at ("parent").as_object ();
  EventBufsVideoScaler ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufs > (), pobj));

  ret.type_       = ::boost::json::value_to< Scalers > (jvs.at ("type"));
  ret.koeff_pow2_ = ::libs::utility::json::get_int32 (jvs.at ("koeff_pow2"));
  return ret;
}
}   // namespace libs::events_base::props::videos::generic::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::scaler::EventBufsVideoScaler);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::scaler::EventBufsVideoScaler);
