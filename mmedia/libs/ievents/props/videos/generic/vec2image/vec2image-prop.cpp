/**
\file       Vec2ImageProp.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "vec2image-prop.hpp"

namespace libs::ievents::props::videos::generic::vec2image
{
Vec2ImageProp::Vec2ImageProp (const Acessor&, const vec_bufs_type& bufs) :
  bufs_ (bufs)
{
  property_name_ = gen_get_mid ();
}


Vec2ImageProp::~Vec2ImageProp ()
{
}


::libs::events::IEvent::ptr
Vec2ImageProp::clone_int (const ::libs::events::Deeps& deep) const
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
  U3_CHECK_COPY_EVENT (Vec2ImageProp);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
Vec2ImageProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp);
