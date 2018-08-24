//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-event-info.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buff-event-info.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace motion_est {

void
BuffEventInfo::check () const
{
  super::check ();

  CHECK_STATE (min_error_ < max_error_, "failed, min large max");
  CHECK_STATE (min_error_ >= 0.0f, "failed, min large 0");
  CHECK_STATE (max_error_ > 0.0f, "failed, max less 0");
  CHECK_STATE (8 == size_block_ || 16 == size_block_ || 32 == size_block_, "failed, invalid blok size");
  CHECK_STATE (size_search_ > 0, "failed, size search less 0");
  CHECK_STATE (size_search_ <= 126, "failed, size search large 126");      // 127 reserved for invalid
  return;
}


void
BuffEventInfo::load_int (const base_functs::xml::itn& _node)
{
  if (pugi::xml_attribute _attr = _node->attribute ("max_error"))
    {
      max_error_ = _attr.as_float ();
    }

  if (pugi::xml_attribute _attr = _node->attribute ("min_error"))
    {
      min_error_ = _attr.as_float ();
    }

  if (pugi::xml_attribute _attr = _node->attribute ("size_block"))
    {
      size_block_ = UUU_ICAST_SHORT (_attr.as_int ());
    }

  if (pugi::xml_attribute _attr = _node->attribute ("size_search"))
    {
      size_search_ = UUU_ICAST_SHORT (_attr.as_int ());
    }

  check ();
  return;
}


template <class Archive>
void
BuffEventInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (max_error_);
  ar& BOOST_SERIALIZATION_NVP (min_error_);
  ar& BOOST_SERIALIZATION_NVP (size_block_);
  ar& BOOST_SERIALIZATION_NVP (size_search_);
  ar& BOOST_SERIALIZATION_NVP (search_vecs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::motion_est

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::motion_est::BuffEventInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::motion_est::BuffEventInfo);
