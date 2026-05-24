/**
\file       video-histogram-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-histogram-prop.hpp"

namespace libs::ievents::props::videos::generic::histogram
{
EventBufsInfoHistogram::EventBufsInfoHistogram () :
  norm_ (false), dindx_ (-1)
{
}


template< class Archive >
void
EventBufsInfoHistogram::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (norm_);
  ar& BOOST_SERIALIZATION_NVP (dindx_);
}


VideoHistogramProp::VideoHistogramProp (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


VideoHistogramProp::~VideoHistogramProp ()
{
}


::libs::events::IEvent::ptr
VideoHistogramProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoHistogramProp > (this, deep);
}


void
VideoHistogramProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
VideoHistogramProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
VideoHistogramProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (VideoHistogramProp);
  super::copy_int (src);
  bufs2norm_ = dsrc->bufs2norm_;
}


template< class Archive >
void
VideoHistogramProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (bufs2norm_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::histogram

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::histogram::EventBufsInfoHistogram);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::histogram::EventBufsInfoHistogram);

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::histogram::VideoHistogramProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::histogram::VideoHistogramProp);
