/**
\file       base-id-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       18.07.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "base-id-prop.hpp"

namespace libs::events_base::props::base_id
{
BaseIdProp::BaseIdProp (const Acessor& pha)
{
  buf2modules_.emplace_back (0.0F, ::utils::dbufs::video::consts::offs::http, "u3m_http");
  buf2modules_.emplace_back (0.0F, ::utils::dbufs::video::consts::offs::http, "u3m_store");
  state_ = events::PropertyUsings::enabled;
}


auto
BaseIdProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseIdProp::gen_get_mid ();
}


auto
BaseIdProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseIdProp > (src);
  super::copy_int (src);

  source_name_ = dsrc->source_name_;
  buf2modules_ = dsrc->buf2modules_;
}


template< class Archive >
void
BaseIdProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (source_name_);
  arh& BOOST_SERIALIZATION_NVP (buf2modules_);

  self_correct ();
}
}   // namespace libs::events_base::props::base_id

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::base_id::BaseIdProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::base_id::BaseIdProp);
