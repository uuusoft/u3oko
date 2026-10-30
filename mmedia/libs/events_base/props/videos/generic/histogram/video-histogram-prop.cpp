/**
\file       video-histogram-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-histogram-prop.hpp"

namespace libs::events_base::props::videos::generic::histogram
{
#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
EventBufsHistogram::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (norm_);
  arh& BOOST_SERIALIZATION_NVP (dindx_);
}
#endif

VideoHistogramProp::VideoHistogramProp (const Acessor& pha)
{
}


auto
VideoHistogramProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoHistogramProp::gen_get_mid ();
}


auto
VideoHistogramProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoHistogramProp > (this, deep);
}


void
VideoHistogramProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  ::libs::utility::checks::assert_soft (0, "???");
}


void
VideoHistogramProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  ::libs::utility::checks::assert_soft (0, "???");
}


void
VideoHistogramProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoHistogramProp > (src);
  super::copy_int (src);
  bufs2norm_ = dsrc->bufs2norm_;
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
VideoHistogramProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs2norm_);

  self_correct ();
}
#endif
}   // namespace libs::events_base::props::videos::generic::histogram

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::histogram::EventBufsHistogram);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::histogram::EventBufsHistogram);

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::histogram::VideoHistogramProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::histogram::VideoHistogramProp);
