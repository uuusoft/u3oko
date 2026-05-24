/**
\file       video-scaler-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-scaler-prop.hpp"

namespace libs::ievents::props::videos::generic::scaler
{
VideoScalerProp::VideoScalerProp (const Acessor& ph) :
  bufs_ ({ EventBufsInfoVideoScaler (utils::dbufs::video::consts::offs::lit, utils::dbufs::video::consts::offs::lit) })
{
  property_name_ = gen_get_mid ();
}


VideoScalerProp::~VideoScalerProp ()
{
}


const VideoScalerProp::bufs_type&
VideoScalerProp::get_bufs () const
{
  return bufs_;
}


::libs::events::IEvent::ptr
VideoScalerProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoScalerProp > (this, deep);
}


void
VideoScalerProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  bufs_ = ::boost::json::value_to< bufs_type > (obj.at ("evbufs"));
}


void
VideoScalerProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["evbufs"] = ::boost::json::value_from (bufs_);
}


void
VideoScalerProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (VideoScalerProp);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
VideoScalerProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::scaler::VideoScalerProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::scaler::VideoScalerProp);
