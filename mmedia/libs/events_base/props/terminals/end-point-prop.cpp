/**
\file       end-point-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../events-base-includes_int.hpp"
#include "end-point-prop.hpp"

namespace libs::events_base::props::terminals
{
EndPointProp::EndPointProp (const Acessor& pha)
{
  state_ = events::PropertyUsings::enabled;
}


auto
EndPointProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return EndPointProp::gen_get_mid ();
}


auto
EndPointProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< EndPointProp > (this, deep);
}


void
EndPointProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  enable_send_   = obj.at ("enable_send").as_bool ();
  enable_notify_ = obj.at ("enable_notify").as_bool ();
}


void
EndPointProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["enable_send"]   = enable_send_;
  obj["enable_notify"] = enable_notify_;
}


auto
EndPointProp::is_send () const -> bool
{
  return enable_send_;
}


auto
EndPointProp::is_notify () const -> bool
{
  return enable_notify_;
}


void
EndPointProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< EndPointProp > (src);
  super::copy_int (src);

  enable_send_   = dsrc->enable_send_;
  enable_notify_ = dsrc->enable_notify_;
}


template< class Archive >
void
EndPointProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (enable_send_);
  arh& BOOST_SERIALIZATION_NVP (enable_notify_);

  self_correct ();
}
}   // namespace libs::events_base::props::terminals

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::terminals::EndPointProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::terminals::EndPointProp);
