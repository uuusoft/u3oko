/**
\file       video-scaler-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-scaler-prop.hpp"

namespace libs::events_base::props::videos::generic::scaler
{
VideoScalerProp::VideoScalerProp (const Acessor& pha) :
  bufs_ ({ EventBufsVideoScaler (utils::dbufs::video::consts::offs::lit, utils::dbufs::video::consts::offs::lit) })
{
}


auto
VideoScalerProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoScalerProp::gen_get_mid ();
}


auto
VideoScalerProp::get_bufs () const -> const VideoScalerProp::bufs_type&
{
  return bufs_;
}


auto
VideoScalerProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoScalerProp > (src);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
VideoScalerProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::scaler::VideoScalerProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::scaler::VideoScalerProp);
