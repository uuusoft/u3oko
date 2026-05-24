/**
\file       VideoConvertProp.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  const convert_type conv = {
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

  const convert_type conv = {
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


VideoConvertProp::VideoConvertProp (const Acessor& ph) :
  rwidth_ (100),
  rheight_ (100),
  rtype_ (Src2DstEqs::src_int_dst),
  duplicate_image_ (false),
  strip_color_ (false),
  debug_skip_transform_ (false),
  flip_y_ (false),
  atype_ (Accuracys::usual),
  buf_ (::utils::dbufs::video::consts::offs::raw, ::utils::dbufs::video::consts::offs::invalid)
{
  property_name_ = gen_get_mid ();
}


VideoConvertProp::~VideoConvertProp ()
{
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

  // buf_.load_json (obj);
  rtype_                = src2dst_from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("rtype")));
  atype_                = U3_CAST_STATIC< Accuracys > (::libs::helpers::json::get_uint32 (obj.at ("atype")));
  rwidth_               = ::libs::helpers::json::get_uint32 (obj.at ("rwidth"));
  rheight_              = ::libs::helpers::json::get_uint32 (obj.at ("rheight"));
  duplicate_image_      = obj.at ("duplicate_image").as_bool ();
  strip_color_          = obj.at ("strip_color").as_bool ();
  debug_skip_transform_ = obj.at ("debug_skip_transform").as_bool ();
  flip_y_               = obj.at ("flip_y").as_bool ();
  buf_                  = ::boost::json::value_to< ::libs::events::buf::EventBufsInfo > (obj.at ("evbufs"));
}


void
VideoConvertProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  // buf_.save_json (obj);
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
  U3_CHECK_COPY_EVENT (VideoConvertProp);
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
VideoConvertProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  ar& BOOST_SERIALIZATION_NVP (buf_);
  ar& BOOST_SERIALIZATION_NVP (rwidth_);
  ar& BOOST_SERIALIZATION_NVP (rheight_);
  ar& BOOST_SERIALIZATION_NVP (rtype_);
  ar& BOOST_SERIALIZATION_NVP (duplicate_image_);
  ar& BOOST_SERIALIZATION_NVP (strip_color_);
  ar& BOOST_SERIALIZATION_NVP (debug_skip_transform_);
  ar& BOOST_SERIALIZATION_NVP (flip_y_);
  ar& BOOST_SERIALIZATION_NVP (atype_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::convert

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
