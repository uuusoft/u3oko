/**
\file       info-buf-freq-noise-remover.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "info-buf-freq-noise-remover.hpp"

namespace libs::ievents::props::videos::noises::freq
{
InfoBuffFreqNoiseRemover::InfoBuffFreqNoiseRemover (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst,
  const ::utils::dbufs::video::consts::offs::off_buf_type& bindx_diff,
  std::int16_t                                             bound_x_plus_y,
  float                                                    dwt_koeff2) :

  ::libs::events::buf::EventBufsInfo (src, dst),
  bindx_diff_ (bindx_diff),
  bound_x_plus_y_ (bound_x_plus_y),
  dwt_koeff2_ (dwt_koeff2)
{
}


InfoBuffFreqNoiseRemover::InfoBuffFreqNoiseRemover (const ::libs::events::buf::EventBufsInfo& buf) :
  ::libs::events::buf::EventBufsInfo (buf),
  bindx_diff_ (utils::dbufs::video::consts::offs::invalid),
  bound_x_plus_y_ (1),
  dwt_koeff2_ (1.0F)
{
}


template< class Archive >
void
InfoBuffFreqNoiseRemover::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (bindx_diff_);
  arh& BOOST_SERIALIZATION_NVP (bound_x_plus_y_);
  arh& BOOST_SERIALIZATION_NVP (dwt_koeff2_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const InfoBuffFreqNoiseRemover& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::helpers::casts::static_cast_helper< const ::libs::events::buf::EventBufsInfo& > (src));

  jvs = {
    { "parent", pjv },
    { "bindx_diff", src.bindx_diff_ },
    { "bound_x_plus_y", src.bound_x_plus_y_ },
    { "dwt_koeff2", src.dwt_koeff2_ }
  };
}


InfoBuffFreqNoiseRemover
tag_invoke (::boost::json::value_to_tag< InfoBuffFreqNoiseRemover >, const ::boost::json::value& jvs)
{
  const auto&                  pobj = jvs.at ("parent").as_object ();
  InfoBuffFreqNoiseRemover     ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufsInfo > (), pobj));
  const ::boost::json::object& obj = jvs.as_object ();

  ret.bindx_diff_     = obj.at ("bindx_diff").as_string ();
  ret.bound_x_plus_y_ = ::libs::helpers::json::get_int32 (obj.at ("bound_x_plus_y"));
  ret.dwt_koeff2_     = ::libs::helpers::json::get_float (obj.at ("dwt_koeff2"));
  return ret;
}
}   // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
