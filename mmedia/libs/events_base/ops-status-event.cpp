/**
\file       ops-status-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "ops-status-event.hpp"

namespace libs::events_base
{
OpsStatusEvent::OpsStatusEvent (const Acessor& pha)
{
}


auto
OpsStatusEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return OpsStatusEvent::gen_get_mid ();
}


auto
OpsStatusEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< OpsStatusEvent > (this, deep);
}


auto
OpsStatusEvent::get_ops_status () const -> OpsStatus
{
  return ops_status_;
}


auto
OpsStatusEvent::set_ops_status (const OpsStatus& val) -> void
{
  ops_status_ = val;
}


auto
OpsStatusEvent::get_ops_info () const -> const std::string&
{
  return ops_json_info_;
}


auto
OpsStatusEvent::set_ops_info (const std::string& val) -> void
{
  ops_json_info_ = val;
}


void
OpsStatusEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "OpsStatusEvent::load_json_int: not implemented");
}


void
OpsStatusEvent::save_json_int (::boost::json::object& jsn) const
{
  super::save_json_int (jsn);

  jsn["ops_status"]    = U3_CAST_INT32_FORCE (ops_status_);
  jsn["ops_json_info"] = ops_json_info_;
  // jsn["ops_json_info"]  = ::boost::json::serialize(ops_json_info_);
}


void
OpsStatusEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< OpsStatusEvent > (src);
  super::copy_int (src);
  ops_status_    = dsrc->ops_status_;
  ops_json_info_ = dsrc->ops_json_info_;
}


template< class Archive >
void
OpsStatusEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", ::libs::events_base::Event);
  arh& BOOST_SERIALIZATION_NVP (ops_status_);
  arh& BOOST_SERIALIZATION_NVP (ops_json_info_);
  self_correct ();
}
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::OpsStatusEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::OpsStatusEvent);
