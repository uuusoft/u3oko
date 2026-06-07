/**
\file       video-diff-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-diff-prop.hpp"

namespace libs::ievents::props::videos::gens::diff
{
void
load_op (const ::pugi::xml_named_node_iterator& prop, ParamsVideoDiffProp& info)
{
  if (pugi::xml_attribute ext_name = prop->attribute ("enable"))
  {
    info.enable_ = ext_name.as_bool ();
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("bound_filling"))
  {
    info.bound_filling_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("val_filling"))
  {
    info.val_filling_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }
}


VideoDiffProp::VideoDiffProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoDiffProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoDiffProp > (this, deep);
}


void
VideoDiffProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
VideoDiffProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
VideoDiffProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoDiffProp > (src);
  super::copy_int (src);
  diffs_ = dsrc->diffs_;
}


template< class Archive >
void
VideoDiffProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (diffs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
