//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       VideoConvertProp.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-convert-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convert {

TypeSrc2Dst
str2size_type (const std::string& _str)
{
  using convert_type = std::map<std::string, TypeSrc2Dst>;

  const convert_type _conv = {
    convert_type::value_type ("src_int_dst", TypeSrc2Dst::src_int_dst),
    convert_type::value_type ("src_int_dst2", TypeSrc2Dst::src_int_dst2),
    convert_type::value_type ("equal_dst", TypeSrc2Dst::equal_dst),
    convert_type::value_type ("additive", TypeSrc2Dst::additive)
  };

  const auto _find = _conv.find (_str);
  if (_find == _conv.end ())
    {
      UASSERT_SIGNAL ("failed");
      return TypeSrc2Dst::equal_dst;
    }
  return _find->second;
}


TypeConvertAccuracy
str2atype (const std::string& _str)
{
  using convert_type = std::map<std::string, TypeConvertAccuracy>;

  const convert_type _conv = {
    convert_type::value_type ("default", TypeConvertAccuracy::usual),
    convert_type::value_type ("fast", TypeConvertAccuracy::fast),
    convert_type::value_type ("best", TypeConvertAccuracy::best)
  };

  const auto _find = _conv.find (_str);
  if (_find == _conv.end ())
    {
      UASSERT_SIGNAL ("failed");
      return TypeConvertAccuracy::usual;
    }
  return _find->second;
}


VideoConvertProp::VideoConvertProp (const Acessor& _ph) :
  rwidth_ (100),
  rheight_ (100),
  rtype_ (TypeSrc2Dst::src_int_dst),
  duplicate_image_ (false),
  strip_color_ (false),
  debug_skip_transform_ (false),
  flip_y_ (false),
  atype_ (TypeConvertAccuracy::usual),
  buff_ (::utils::dbuffs::video::consts::offs::raw, ::utils::dbuffs::video::consts::offs::invalid)
{
  property_name_ = gen_get_type_text_id ();
}


VideoConvertProp::~VideoConvertProp ()
{}


::libs::events::IEvent::ptr
VideoConvertProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoConvertProp> (this, _deep);
}


void
VideoConvertProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<int> (_param, "width", rwidth_);
      ::libs::icore::xml::helpers::load<int> (_param, "height", rheight_);

      ::libs::icore::xml::helpers::load (
        _param,
        "size type",
        [this](const std::string& _val) {
          rtype_ = str2size_type (_val);
          return;
        });

      ::libs::icore::xml::helpers::load (
        _param,
        "accuracy type",
        [this](const std::string& _val) {
          atype_ = str2atype (_val);
          return;
        });

      ::libs::icore::xml::helpers::load<bool> (_param, "duplicate_image", duplicate_image_);
      ::libs::icore::xml::helpers::load<bool> (_param, "strip_color", strip_color_);
      ::libs::icore::xml::helpers::load<bool> (_param, "debug_skip_transform", debug_skip_transform_);
      ::libs::icore::xml::helpers::load<bool> (_param, "flip_y", flip_y_);

      ++_param;
    }

  {
    base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
    base_functs::xml::itn  _param  = _params.begin ();

    while (_param != _params.end ())
      {
        buff_.load (_param);
        buff_.check (true, false);
        ++_param;
      }
  }

  self_correct ();
  return;
}


void
VideoConvertProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoConvertProp);
  super::copy_int (_src);

  buff_                 = _dsrc->buff_;
  rwidth_               = _dsrc->rwidth_;
  rheight_              = _dsrc->rheight_;
  rtype_                = _dsrc->rtype_;
  duplicate_image_      = _dsrc->duplicate_image_;
  strip_color_          = _dsrc->strip_color_;
  debug_skip_transform_ = _dsrc->debug_skip_transform_;
  flip_y_               = _dsrc->flip_y_;
  atype_                = _dsrc->atype_;
  return;
}


template <class Archive>
void
VideoConvertProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);

  ar& BOOST_SERIALIZATION_NVP (buff_);
  ar& BOOST_SERIALIZATION_NVP (rwidth_);
  ar& BOOST_SERIALIZATION_NVP (rheight_);
  ar& BOOST_SERIALIZATION_NVP (rtype_);
  ar& BOOST_SERIALIZATION_NVP (duplicate_image_);
  ar& BOOST_SERIALIZATION_NVP (strip_color_);
  ar& BOOST_SERIALIZATION_NVP (debug_skip_transform_);
  ar& BOOST_SERIALIZATION_NVP (flip_y_);
  ar& BOOST_SERIALIZATION_NVP (atype_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::convert

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::convert::VideoConvertProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::convert::VideoConvertProp);
