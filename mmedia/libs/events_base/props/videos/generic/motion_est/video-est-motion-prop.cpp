/**
\file       video-est-motion-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-est-motion-prop.hpp"

namespace libs::events_base::props::videos::generic::motion_est
{
VideoEstMotionProp::VideoEstMotionProp (const Acessor& pha) :
  bufs_ ({ EventBufsMotionEst (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::move_est_res) })
{
}


auto
VideoEstMotionProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoEstMotionProp::gen_get_mid ();
}


auto
VideoEstMotionProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoEstMotionProp > (this, deep);
}


void
VideoEstMotionProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  bufs_ = ::boost::json::value_to< bufs_type > (obj.at ("evbufs"));
}


void
VideoEstMotionProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["evbufs"] = ::boost::json::value_from (bufs_);
}


void
VideoEstMotionProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoEstMotionProp > (src);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
VideoEstMotionProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp);
