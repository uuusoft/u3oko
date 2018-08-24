//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-event-info-vec2image1.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buff-event-info-vec2image1.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace vec2image {

void
BuffEventInfoVec2Image1::check () const
{
  super::check ();

  CHECK_STATE (8 == size_block_ || 16 == size_block_ || 32 == size_block_, "failed, size block invalid");
  CHECK_STATE (mul_koeff_vec_ > 0, "failed, mul koeff less 0");
  return;
}


void
BuffEventInfoVec2Image1::load_int (const base_functs::xml::itn& _node)
{
  if (pugi::xml_attribute _attr = _node->attribute ("size_block"))
    {
      size_block_ = UUU_ICAST_SHORT (_attr.as_int ());
    }

  if (pugi::xml_attribute _attr = _node->attribute ("mul_koeff_vec"))
    {
      mul_koeff_vec_ = UUU_ICAST_SHORT (_attr.as_int ());
    }

  check ();
  return;
}


template <class Archive>
void
BuffEventInfoVec2Image1::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (size_block_);
  ar& BOOST_SERIALIZATION_NVP (mul_koeff_vec_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::vec2image::BuffEventInfoVec2Image1);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::vec2image::BuffEventInfoVec2Image1);
