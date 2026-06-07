/**
\file       video-est-motion-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-est-motion-prop.hpp"

namespace libs::ievents::props::videos::generic::motion_est
{
VideoEstMotionProp::VideoEstMotionProp (const Acessor& pha) :
  bufs_ ({ EventBufsInfoMotionEst (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::move_est_res) })
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoEstMotionProp::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp);
