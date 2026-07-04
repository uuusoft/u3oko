/**
\file       Vec2ImageProp.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "vec2image-prop.hpp"

namespace libs::events_base::props::videos::generic::vec2image
{
Vec2ImageProp::Vec2ImageProp (const Acessor&, vec_bufs_type bufs) :
  bufs_ (std::move (bufs))
{
}


auto
Vec2ImageProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return Vec2ImageProp::gen_get_mid ();
}


auto
Vec2ImageProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< Vec2ImageProp > (this, deep);
}


void
Vec2ImageProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  bufs_ = ::boost::json::value_to< Vec2ImageProp::vec_bufs_type > (obj.at ("evbufs"));
}


void
Vec2ImageProp::save_json_int (::boost::json::object& obj) const
{
  U3_XLOG_DBG ("Vec2ImageProp::save_json_int");
  super::save_json_int (obj);

  obj["evbufs"] = ::boost::json::value_from (bufs_);
}


void
Vec2ImageProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< Vec2ImageProp > (src);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
Vec2ImageProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::vec2image::Vec2ImageProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::vec2image::Vec2ImageProp);
