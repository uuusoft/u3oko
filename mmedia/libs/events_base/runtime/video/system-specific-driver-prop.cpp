/**
\file       system-specific-driver-prop.cpp
\date       08.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "system-specific-driver-prop.hpp"

namespace libs::events_base::runtime::video
{
SystemSpecificDriverProp::SystemSpecificDriverProp (const Acessor& pha)
{
}


auto
SystemSpecificDriverProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return SystemSpecificDriverProp::gen_get_mid ();
}


auto
SystemSpecificDriverProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< SystemSpecificDriverProp > (this, deep);
}


void
SystemSpecificDriverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  show_system_page_ = obj.at ("show_system_page").as_bool ();
}


void
SystemSpecificDriverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["show_system_page"] = show_system_page_;
}


void
SystemSpecificDriverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< SystemSpecificDriverProp > (src);
  super::copy_int (src);
  show_system_page_ = dsrc->show_system_page_;
}


template< class Archive >
void
SystemSpecificDriverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (show_system_page_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::video::SystemSpecificDriverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::video::SystemSpecificDriverProp);
