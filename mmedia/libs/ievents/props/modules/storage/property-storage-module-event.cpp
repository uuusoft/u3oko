/**
\file       property-storage-module-event.cpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "property-storage-module-event.hpp"

namespace libs::ievents::props::modules::storage
{
PropertyStorageModuleEvent::PropertyStorageModuleEvent (const Acessor& ph) :
  check_ (Checkers::start_stop)
{
  property_name_ = gen_get_mid ();
}


PropertyStorageModuleEvent::~PropertyStorageModuleEvent ()
{
}


const PropertyStorageModuleEvent::paths_type&
PropertyStorageModuleEvent::get_paths () const
{
  return paths_;
}


const Checkers&
PropertyStorageModuleEvent::get_check () const
{
  return check_;
}


::libs::events::IEvent::ptr
PropertyStorageModuleEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< PropertyStorageModuleEvent > (this, deep);
}


void
PropertyStorageModuleEvent::load_json_int (const ::boost::json::object& obj)
{
  U3_ASSERT_NT (0, "???");
}


void
PropertyStorageModuleEvent::save_json_int (::boost::json::object& obj) const
{
  U3_ASSERT_NT (0, "???");
}


void
PropertyStorageModuleEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (PropertyStorageModuleEvent);
  super::copy_int (src);

  paths_ = dsrc->paths_;
  check_ = dsrc->check_;
}


template< class Archive >
void
PropertyStorageModuleEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (paths_);
  ar& BOOST_SERIALIZATION_NVP (check_);

  self_correct ();
}
}   // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
