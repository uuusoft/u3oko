/**
\file       change-state-event.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../events-base-includes_int.hpp"
#include "change-state-event.hpp"

namespace libs::events_base::runtime::state
{
ChangeStateProcessEvent::ChangeStateProcessEvent (const Acessor& pha, bool start) :
  start_ (start)
{
}


auto
ChangeStateProcessEvent::is_start () const -> bool
{
  return start_;
}


void
ChangeStateProcessEvent::set_start (bool val)
{
  start_ = val;
}


auto
ChangeStateProcessEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ChangeStateProcessEvent::gen_get_mid ();
}


void
ChangeStateProcessEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "ChangeStateProcessEvent::load_json_int:: wtf???");
}


void
ChangeStateProcessEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "ChangeStateProcessEvent::save_json_int:: wtf???");
}


auto
ChangeStateProcessEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ChangeStateProcessEvent > (this, deep);
}


void
ChangeStateProcessEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ChangeStateProcessEvent > (src);
  super::copy_int (src);
  start_ = dsrc->start_;
}


template< class Archive >
void
ChangeStateProcessEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (start_);
}
}   // namespace libs::events_base::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::state::ChangeStateProcessEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::state::ChangeStateProcessEvent);
