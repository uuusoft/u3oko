//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-video-convolution-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buff-video-convolution-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convolution {

BuffVideoConvolutionProp::BuffVideoConvolutionProp () :
  size_ (3),
  koeff_ (0),
  mod_ (false),
  name_ ("user")
{}


void
BuffVideoConvolutionProp::load_int (const base_functs::xml::itn& _node)
{
  check ();
  return;
}


void
BuffVideoConvolutionProp::check () const
{
  super::check ();
  CHECK_STATE (size_ >= 3, "failed, size core less 3");
  CHECK_STATE (size_ <= 11, "failed, size core large 11");
  CHECK_STATE (vals_.size () == UUU_ICAST_SIZE_T (size_ * size_), "failed, invalid vals core");
  return;
}


template <class Archive>
void
BuffVideoConvolutionProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (size_);
  ar& BOOST_SERIALIZATION_NVP (vals_);
  ar& BOOST_SERIALIZATION_NVP (koeff_);
  ar& BOOST_SERIALIZATION_NVP (name_);
  ar& BOOST_SERIALIZATION_NVP (mod_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::convolution

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::convolution::BuffVideoConvolutionProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::convolution::BuffVideoConvolutionProp);
