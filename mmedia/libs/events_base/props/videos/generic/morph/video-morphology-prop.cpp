/**
\file       video-morphology-prop.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-morphology-prop.hpp"

namespace libs::events_base::props::videos::generic::morph
{
void
load_op (const ::pugi::xml_named_node_iterator& prop, MorphOperationParams& info)
{
  pugi::xml_attribute name_op = prop->attribute ("name");

  if (!name_op)
  {
    U3_ASSERT_SIGNAL ("failed");
    return;
  }

  info.morph_type_ = str2type_morph_op (name_op.as_string ());

  if (pugi::xml_attribute ext_name = prop->attribute ("bound_filling"))
  {
    info.bound_filling_ = ::libs::utility::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("val_filling"))
  {
    info.val_filling_ = ::libs::utility::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("size_spot"))
  {
    info.size_spot_ = ::libs::utility::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (1), U3_CAST_INT16 (9));
  }
}


VideoMorphologyProp::VideoMorphologyProp (const Acessor& pha)
{
  MorphBuffInfo::morph_operations_type default_ops (3);
  const auto                           default_morph_buf_info = MorphBuffInfo (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit, default_ops);

  diffs_.clear ();
  diffs_.reserve (3);
  diffs_.emplace_back (default_morph_buf_info);
  diffs_.emplace_back (default_morph_buf_info);
  diffs_.emplace_back (default_morph_buf_info);
}


auto
VideoMorphologyProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoMorphologyProp::gen_get_mid ();
}


auto
VideoMorphologyProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoMorphologyProp > (this, deep);
}


void
VideoMorphologyProp::load_json_int (const ::boost::json::object& obj)
{
  // U3_XLOG_DEV ("VideoMorphologyProp::load_json_int");
  super::load_json_int (obj);

  diffs_ = ::boost::json::value_to< VideoMorphologyProp::morph_buf_infos_type > (obj.at ("diffs"));
}


void
VideoMorphologyProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["diffs"] = ::boost::json::value_from (diffs_);
}


void
VideoMorphologyProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoMorphologyProp > (src);
  super::copy_int (src);
  diffs_ = dsrc->diffs_;
}


template< class Archive >
void
VideoMorphologyProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (diffs_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::morph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::morph::VideoMorphologyProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::morph::VideoMorphologyProp);
