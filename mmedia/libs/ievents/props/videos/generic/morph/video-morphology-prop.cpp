/**
\file       video-morphology-prop.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-morphology-prop.hpp"

namespace libs::ievents::props::videos::generic::morph
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
    info.bound_filling_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("val_filling"))
  {
    info.val_filling_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (0), U3_CAST_INT16 (255));
  }

  if (pugi::xml_attribute ext_name = prop->attribute ("size_spot"))
  {
    info.size_spot_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ext_name.as_int (), U3_CAST_INT16 (1), U3_CAST_INT16 (9));
  }
}


VideoMorphologyProp::VideoMorphologyProp (const Acessor& ph)
{
  property_name_ = gen_get_mid ();

  MorphBuffInfo::morph_operations_type default_ops (3);
  const auto                           default_morph_buf_info = MorphBuffInfo (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit, default_ops);

  diffs_.clear ();
  diffs_.reserve (3);

  diffs_.emplace_back (default_morph_buf_info);
  diffs_.emplace_back (default_morph_buf_info);
  diffs_.emplace_back (default_morph_buf_info);
}


VideoMorphologyProp::~VideoMorphologyProp ()
{
}


::libs::events::IEvent::ptr
VideoMorphologyProp::clone_int (const ::libs::events::Deeps& deep) const
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
  U3_CHECK_COPY_EVENT (VideoMorphologyProp);
  super::copy_int (src);
  diffs_ = dsrc->diffs_;
}


template< class Archive >
void
VideoMorphologyProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (diffs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
