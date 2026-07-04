/**
\file       buf-video-time-noise-remover-prop.cpp
\date       01.07.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../../../events-base-includes_int.hpp"
#include "buf-video-time-noise-remover-prop.hpp"

namespace libs::events_base::props::videos::noises::time
{
BuffVideoTimeNoiseRemoverProp::BuffVideoTimeNoiseRemoverProp (
  const syn::off_buf_type& src,
  const syn::off_buf_type& dst) :
  ::libs::events::buf::EventBufs (src, dst)
{
}


BuffVideoTimeNoiseRemoverProp::BuffVideoTimeNoiseRemoverProp (
  const ::libs::events::buf::EventBufs& buf) :
  ::libs::events::buf::EventBufs (buf)
{
}


void
BuffVideoTimeNoiseRemoverProp::check_int ()
{
}


void
BuffVideoTimeNoiseRemoverProp::correct_int ()
{
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
BuffVideoTimeNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BuffVideoTimeNoiseRemoverProp > (src);
  super::copy_int (src);

  impl_info_ = ::libs::iproperties::helpers::clone_event (dsrc->impl_info_.get ());
}
#endif

template< class Archive >
void
BuffVideoTimeNoiseRemoverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoeventsobufoEventBufs", super);
  arh& BOOST_SERIALIZATION_NVP (impl_info_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const BuffVideoTimeNoiseRemoverProp& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (tag, pjv, ::libs::utility::casts::static_cast_helper< const ::libs::events::buf::EventBufs& > (src));

  // EAI-REFACT
  auto impl_info = src.impl_info_ ? src.impl_info_ : ::libs::iproperties::helpers::get_pure_event_int (ext::MedianTimeFilterProp::gen_get_mid ());

  jvs = {
    { "parent", pjv },
    { "impl_info-id", impl_info->get_mid () },
    { "impl_info", impl_info->save_json () }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< BuffVideoTimeNoiseRemoverProp >, const ::boost::json::value& jvs) -> BuffVideoTimeNoiseRemoverProp
{
  const auto&                   pobj = jvs.at ("parent").as_object ();
  BuffVideoTimeNoiseRemoverProp ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufs > (), pobj));
  const auto&                   obj              = jvs.as_object ();
  const std::string             raw_impl_info_id = obj.at ("impl_info-id").is_string () ? obj.at ("impl_info-id").as_string ().c_str () : "";
  const auto                    impl_info_id     = raw_impl_info_id.empty () ? std::string { ext::MedianTimeFilterProp::gen_get_mid () } : raw_impl_info_id;

  ret.impl_info_ = ::libs::iproperties::helpers::get_pure_event_int (impl_info_id.c_str ());
  if (ret.impl_info_)
  {
    ret.impl_info_->load_json (obj.at ("impl_info").as_string ().c_str ());
  }
  return ret;
}
}   // namespace libs::events_base::props::videos::noises::time

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::time::BuffVideoTimeNoiseRemoverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::time::BuffVideoTimeNoiseRemoverProp);
