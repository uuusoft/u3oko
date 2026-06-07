/**
\file       buf-event-info-video-scaler.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buf-event-info-video-scaler.hpp"

namespace libs::ievents::props::videos::generic::scaler
{
EventBufsInfoVideoScaler::EventBufsInfoVideoScaler (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst) :

  ::libs::events::buf::EventBufsInfo (src, dst),
  type_ (Scalers::nearest),
  koeff_pow2_ (0)
{
}


EventBufsInfoVideoScaler::EventBufsInfoVideoScaler (const ::libs::events::buf::EventBufsInfo& buf) :
  ::libs::events::buf::EventBufsInfo (buf)
{
}


template< class Archive >
void
EventBufsInfoVideoScaler::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsobufoEventBufsInfo", super);
  arh& BOOST_SERIALIZATION_NVP (type_);
  arh& BOOST_SERIALIZATION_NVP (src_rect_);
  arh& BOOST_SERIALIZATION_NVP (dst_rect_);
  arh& BOOST_SERIALIZATION_NVP (koeff_pow2_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const EventBufsInfoVideoScaler& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::helpers::casts::static_cast_helper< const ::libs::events::buf::EventBufsInfo& > (src));

  jvs = {
    { "parent", pjv },
    { "type", ::boost::json::value_from (src.type_) },
    { "koeff_pow2", src.koeff_pow2_ }
    //{ "src_rect", src.src_rect_ },
    //{ "dst_rect", src.dst_rect_ }
  };
}


EventBufsInfoVideoScaler
tag_invoke (::boost::json::value_to_tag< EventBufsInfoVideoScaler >, const ::boost::json::value& jvs)
{
  const auto&              pobj = jvs.at ("parent").as_object ();
  EventBufsInfoVideoScaler ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufsInfo > (), pobj));
  // const ::boost::json::object& obj = jvs.as_object ();

  ret.type_       = ::boost::json::value_to< Scalers > (jvs.at ("type"));
  ret.koeff_pow2_ = ::libs::helpers::json::get_int32 (jvs.at ("koeff_pow2"));
  // ret.src_rect_   = ::boost::json::value_to< ::libs::events::props::details::Rect > (jvs.at ("src_rect"));
  // ret.dst_rect_   = ::boost::json::value_to< ::libs::events::props::details::Rect > (jvs.at ("dst_rect"));
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::scaler::EventBufsInfoVideoScaler);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::scaler::EventBufsInfoVideoScaler);
