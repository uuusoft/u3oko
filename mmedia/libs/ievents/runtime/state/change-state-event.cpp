/**
\file       change-state-event.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "change-state-event.hpp"

namespace libs::ievents::runtime::state
{
ChangeStateProcessEvent::ChangeStateProcessEvent (const Acessor& pha, bool start) :
  start_ (start)
{
  property_name_ = gen_get_mid ();
}


bool
ChangeStateProcessEvent::is_start () const
{
  return start_;
}


void
ChangeStateProcessEvent::set_start (bool val)
{
  start_ = val;
}


void
ChangeStateProcessEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
ChangeStateProcessEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


::libs::events::IEvent::ptr
ChangeStateProcessEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (start_);
}
}   // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::state::ChangeStateProcessEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::state::ChangeStateProcessEvent);
