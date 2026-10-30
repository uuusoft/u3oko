/**
\file       property-storage-module-event.cpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../events-base-includes_int.hpp"
#include "property-storage-module-event.hpp"

namespace libs::events_base::props::modules::storage
{
PropertyStorageModuleEvent::PropertyStorageModuleEvent (const Acessor& pha) :
  check_ (Checkers::start_stop)
{
}


auto
PropertyStorageModuleEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return PropertyStorageModuleEvent::gen_get_mid ();
}


auto
PropertyStorageModuleEvent::get_paths () const -> const PropertyStorageModuleEvent::paths_type&
{
  return paths_;
}


auto
PropertyStorageModuleEvent::get_check () const -> const Checkers&
{
  return check_;
}


auto
PropertyStorageModuleEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< PropertyStorageModuleEvent > (this, deep);
}


void
PropertyStorageModuleEvent::load_json_int (const ::boost::json::object& obj)
{
  ::libs::utility::checks::assert_soft (0, "???");
}


void
PropertyStorageModuleEvent::save_json_int (::boost::json::object& obj) const
{
  ::libs::utility::checks::assert_soft (0, "???");
}


void
PropertyStorageModuleEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< PropertyStorageModuleEvent > (src);
  super::copy_int (src);

  paths_ = dsrc->paths_;
  check_ = dsrc->check_;
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
PropertyStorageModuleEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (paths_);
  arh& BOOST_SERIALIZATION_NVP (check_);

  self_correct ();
}
#endif
}   // namespace libs::events_base::props::modules::storage

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::modules::storage::PropertyStorageModuleEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::modules::storage::PropertyStorageModuleEvent);
