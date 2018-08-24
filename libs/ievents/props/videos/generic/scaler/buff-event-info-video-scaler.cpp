//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-event-info-video-scaler.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buff-event-info-video-scaler.hpp"


namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace scaler {

TypeScaler
str2type (const std::string& _str)
{
  static const std::pair<std::string, TypeScaler> _vals[] = {
    std::pair<std::string, TypeScaler> ("nearest", TypeScaler::nearest),
    std::pair<std::string, TypeScaler> ("bilinear", TypeScaler::bilinear),
    std::pair<std::string, TypeScaler> ("fixed_pow2", TypeScaler::fixed_pow2)
    //std::pair< std::string, TypeScaler >( "", )
  };

  for (const auto& _val : _vals)
    {
      if (_val.first == _str)
        {
          return _val.second;
        }
    }

  UASSERT_SIGNAL ("failed");
  return TypeScaler::nearest;
}


void
BuffEventInfoVideoScaler::load_int (const base_functs::xml::itn& _node)
{
  if (pugi::xml_attribute _attr = _node->attribute ("type"))
    {
      type_ = str2type (_attr.as_string ());
    }

  auto _childs = _node->children ();

  for (auto& _child : _childs)
    {
      auto _name = _child.attribute ("name");

      if (!_name)
        {
          continue;
        }

      if ("dst rect" == std::string (_name.as_string ()))
        {
          dst_rect_.load (_child);
        }

      if ("src rect" == std::string (_name.as_string ()))
        {
          src_rect_.load (_child);
        }
    }

  check ();
  return;
}


template <class Archive>
void
BuffEventInfoVideoScaler::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (type_);
  ar& BOOST_SERIALIZATION_NVP (src_rect_);
  ar& BOOST_SERIALIZATION_NVP (dst_rect_);
  ar& BOOST_SERIALIZATION_NVP (koeff_pow2_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::scaler::BuffEventInfoVideoScaler);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::scaler::BuffEventInfoVideoScaler);
