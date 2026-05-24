/**
\file       system-specific-driver-prop.cpp
\date       08.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "system-specific-driver-prop.hpp"

namespace libs::ievents::runtime::video
{
SystemSpecificDriverProp::SystemSpecificDriverProp (const Acessor& ph) :
  show_system_page_ (false)
{
  property_name_ = gen_get_mid ();
}


SystemSpecificDriverProp::~SystemSpecificDriverProp ()
{
}


::libs::events::IEvent::ptr
SystemSpecificDriverProp::clone_int (const ::libs::events::Deeps& deep) const
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
  U3_CHECK_COPY_EVENT (SystemSpecificDriverProp);
  super::copy_int (src);
  show_system_page_ = dsrc->show_system_page_;
}


template< class Archive >
void
SystemSpecificDriverProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  ar& BOOST_SERIALIZATION_NVP (show_system_page_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::SystemSpecificDriverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::video::SystemSpecificDriverProp);
