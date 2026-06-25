/**
\file       application-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "application-prop.hpp"

namespace libs::ievents::props::application
{
ApplicationProp::ApplicationProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
  U3_XLOG_DBG ("ApplicationProp::ApplicationProp::---->" + TOLOG (messenger_impl_) + PTR_TOLOG (this));
}


bool
ApplicationProp::is_single_process () const
{
  return single_process_;
}


const std::string&
ApplicationProp::get_messenger_impl () const
{
  U3_XLOG_DBG ("ApplicationProp::get_messenger_impl::---->" + TOLOG (messenger_impl_) + PTR_TOLOG (this));
  return messenger_impl_;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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
  U3_ASSERT_NT (0, "ApplicationProp::load_json_int:: wtf???");
}


void
ApplicationProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "ApplicationProp::save_json_int:: wtf???");
}


void
ApplicationProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ApplicationProp > (src);
  super::copy_int (src);

  U3_XLOG_DBG ("ApplicationProp::copy_int::---->" + TOLOG (messenger_impl_) + PTR_TOLOG (this));
  U3_XLOG_DBG ("ApplicationProp::copy_int::---->" + TOLOG (dsrc->messenger_impl_) + PTR_TOLOG (dsrc));
  single_process_  = dsrc->single_process_;
  messenger_impl_  = dsrc->messenger_impl_;
  machine_name_    = dsrc->machine_name_;
  machine_guid_id_ = dsrc->machine_guid_id_;
}


template< class Archive >
void
ApplicationProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (single_process_);
  arh& BOOST_SERIALIZATION_NVP (messenger_impl_);
  arh& BOOST_SERIALIZATION_NVP (machine_name_);
  arh& BOOST_SERIALIZATION_NVP (machine_guid_id_);
  U3_XLOG_DBG ("ApplicationProp::serialize::---->" + TOLOG (messenger_impl_) + PTR_TOLOG (this));
}
}   // namespace libs::ievents::props::application

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::application::ApplicationProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::application::ApplicationProp);
