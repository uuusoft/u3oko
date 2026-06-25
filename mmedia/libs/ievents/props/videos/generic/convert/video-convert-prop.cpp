/**
\file       VideoConvertProp.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-convert-prop.hpp"

namespace libs::ievents::props::videos::generic::convert
{
Src2DstEqs
str2size_type (const std::string& str)
{
  using convert_type = std::unordered_map< std::string, Src2DstEqs >;

  static const convert_type conv = {
    convert_type::value_type ("src_int_dst", Src2DstEqs::src_int_dst),
    convert_type::value_type ("src_int_dst2", Src2DstEqs::src_int_dst2),
    convert_type::value_type ("equal_dst", Src2DstEqs::equal_dst),
    convert_type::value_type ("additive", Src2DstEqs::additive)
  };

  const auto find = conv.find (str);
  if (find == conv.end ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return Src2DstEqs::equal_dst;
  }
  return find->second;
}


Accuracys
str2atype (const std::string& str)
{
  using convert_type = std::unordered_map< std::string, Accuracys >;

  static const convert_type conv = {
    convert_type::value_type ("default", Accuracys::usual),
    convert_type::value_type ("fast", Accuracys::fast),
    convert_type::value_type ("best", Accuracys::best)
  };

  const auto find = conv.find (str);
  if (find == conv.end ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return Accuracys::usual;
  }
  return find->second;
}


VideoConvertProp::VideoConvertProp (const Acessor& pha)
{
  state_         = events::PropertyUsings::enabled;
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoConvertProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoConvertProp > (this, deep);
}


void
VideoConvertProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  rtype_                = src2dst_from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("rtype")));
  atype_                = ::libs::helpers::casts::static_cast_helper< Accuracys > (::libs::helpers::json::get_uint32 (obj.at ("atype")));
  rwidth_               = ::libs::helpers::json::get_uint32 (obj.at ("rwidth"));
  rheight_              = ::libs::helpers::json::get_uint32 (obj.at ("rheight"));
  duplicate_image_      = obj.at ("duplicate_image").as_bool ();
  strip_color_          = obj.at ("strip_color").as_bool ();
  debug_skip_transform_ = obj.at ("debug_skip_transform").as_bool ();
  flip_y_               = obj.at ("flip_y").as_bool ();
  buf_                  = ::boost::json::value_to< syn::EventBufsInfo > (obj.at ("evbufs"));
}


void
VideoConvertProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["rtype"]                = U3_CAST_UINT32_FORCE (rtype_);
  obj["atype"]                = U3_CAST_UINT32_FORCE (atype_);
  obj["rwidth"]               = rwidth_;
  obj["rheight"]              = rheight_;
  obj["duplicate_image"]      = duplicate_image_;
  obj["strip_color"]          = strip_color_;
  obj["debug_skip_transform"] = debug_skip_transform_;
  obj["flip_y"]               = flip_y_;
  obj["evbufs"]               = ::boost::json::value_from (buf_);
}


void
VideoConvertProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoConvertProp > (src);
  super::copy_int (src);

  buf_                  = dsrc->buf_;
  rwidth_               = dsrc->rwidth_;
  rheight_              = dsrc->rheight_;
  rtype_                = dsrc->rtype_;
  duplicate_image_      = dsrc->duplicate_image_;
  strip_color_          = dsrc->strip_color_;
  debug_skip_transform_ = dsrc->debug_skip_transform_;
  flip_y_               = dsrc->flip_y_;
  atype_                = dsrc->atype_;
}


template< class Archive >
void
VideoConvertProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (buf_);
  arh& BOOST_SERIALIZATION_NVP (rwidth_);
  arh& BOOST_SERIALIZATION_NVP (rheight_);
  arh& BOOST_SERIALIZATION_NVP (rtype_);
  arh& BOOST_SERIALIZATION_NVP (duplicate_image_);
  arh& BOOST_SERIALIZATION_NVP (strip_color_);
  arh& BOOST_SERIALIZATION_NVP (debug_skip_transform_);
  arh& BOOST_SERIALIZATION_NVP (flip_y_);
  arh& BOOST_SERIALIZATION_NVP (atype_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::convert

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
