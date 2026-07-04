/**
\file       info-buf-freq-noise-remover.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "info-buf-freq-noise-remover.hpp"

namespace libs::events_base::props::videos::noises::freq
{
InfoBuffFreqNoiseRemover::InfoBuffFreqNoiseRemover (
  const syn::off_buf_type& src,
  const syn::off_buf_type& dst,
  syn::off_buf_type        bindx_diff,
  std::int16_t             bound_x_plus_y,
  float                    dwt_koeff2) :
  ::libs::events::buf::EventBufs (src, dst),
  bindx_diff_ (std::move (bindx_diff)),
  bound_x_plus_y_ (bound_x_plus_y),
  dwt_koeff2_ (dwt_koeff2)
{
}


InfoBuffFreqNoiseRemover::InfoBuffFreqNoiseRemover (const ::libs::events::buf::EventBufs& buf) :
  ::libs::events::buf::EventBufs (buf)
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
    ::libs::utility::casts::static_cast_helper< const ::libs::events::buf::EventBufs& > (src));

  jvs = {
    { "parent", pjv },
    { "bindx_diff", src.bindx_diff_ },
    { "bound_x_plus_y", src.bound_x_plus_y_ },
    { "dwt_koeff2", src.dwt_koeff2_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< InfoBuffFreqNoiseRemover >, const ::boost::json::value& jvs) -> InfoBuffFreqNoiseRemover
{
  const auto&                  pobj = jvs.at ("parent").as_object ();
  InfoBuffFreqNoiseRemover     ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufs > (), pobj));
  const ::boost::json::object& obj = jvs.as_object ();

  ret.bindx_diff_     = obj.at ("bindx_diff").as_string ();
  ret.bound_x_plus_y_ = ::libs::utility::json::get_int32 (obj.at ("bound_x_plus_y"));
  ret.dwt_koeff2_     = ::libs::utility::json::get_float (obj.at ("dwt_koeff2"));
  return ret;
}
}   // namespace libs::events_base::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
