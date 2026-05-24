/**
\file       application-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "application-prop.hpp"

namespace libs::ievents::props::application
{
ApplicationProp::ApplicationProp (const Acessor& ph) :
  single_process_ (true),
  messenger_impl_ ("fast")
{
  property_name_ = gen_get_mid ();
}


ApplicationProp::~ApplicationProp ()
{
}


bool
ApplicationProp::is_single_process () const
{
  return single_process_;
}


const std::string&
ApplicationProp::get_messenger_impl () const
{
  return messenger_impl_;
}

#if 0
const ApplicationProp::xml_path_folders_type&
ApplicationProp::get_xml_path_folders () const
{
  return xml_data_path_folders_;
}
#endif

::libs::events::IEvent::ptr
ApplicationProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ApplicationProp > (this, deep);
}


void
ApplicationProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
ApplicationProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
ApplicationProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ApplicationProp);
  super::copy_int (src);
  single_process_  = dsrc->single_process_;
  messenger_impl_  = dsrc->messenger_impl_;
  machine_name_    = dsrc->machine_name_;
  machine_guid_id_ = dsrc->machine_guid_id_;
}


template< class Archive >
void
ApplicationProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (single_process_);
  ar& BOOST_SERIALIZATION_NVP (messenger_impl_);
  ar& BOOST_SERIALIZATION_NVP (machine_name_);
  ar& BOOST_SERIALIZATION_NVP (machine_guid_id_);
}
}   // namespace libs::ievents::props::application

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::application::ApplicationProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::application::ApplicationProp);
