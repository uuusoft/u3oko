/**
\file       base-id-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       18.07.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "base-id-prop.hpp"

namespace libs::ievents::props::base_id
{
BaseIdProp::BaseIdProp (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BaseIdProp::~BaseIdProp ()
{
}


::libs::events::IEvent::ptr
BaseIdProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseIdProp > (this, deep);
}


void
BaseIdProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  source_name_ = obj.at ("source_name").as_string ();
  buf2modules_ = ::boost::json::value_to< buf2module_infos_type > (obj.at ("buf2modules"));
}


void
BaseIdProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["source_name"] = source_name_;
  obj["buf2modules"] = ::boost::json::value_from (buf2modules_);
}


void
BaseIdProp::load_buf2module (const ::pugi::xml_named_node_iterator& node, Buff2ModuleInfo* prop)
{
  U3_ASSERT (prop);
  pugi::xml_attribute nfps      = node->attribute ("fps");
  pugi::xml_attribute nindx_buf = node->attribute ("indx_buf");
  pugi::xml_attribute nmodule   = node->attribute ("module");

  if (!nfps || !nindx_buf || !nmodule)
  {
    U3_XLOG_WARN ("BaseIdProp::load_buf2module: skip load, empty attributes" + TOLOG (nfps.as_string ()) + TOLOG (nindx_buf.as_string ()) + TOLOG (nmodule.as_string ()));
    return;
  }

  prop->indx_buf_       = utils::dbufs::video::consts::offs::str2eoffbuf (nindx_buf.as_string ());
  prop->fps_            = nfps.as_float ();
  prop->dest_module_id_ = nmodule.as_string ();
}


void
BaseIdProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BaseIdProp);
  super::copy_int (src);
  source_name_ = dsrc->source_name_;
  buf2modules_ = dsrc->buf2modules_;
}


template< class Archive >
void
BaseIdProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (source_name_);
  ar& BOOST_SERIALIZATION_NVP (buf2modules_);

  self_correct ();
}
}   // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::base_id::BaseIdProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::base_id::BaseIdProp);
