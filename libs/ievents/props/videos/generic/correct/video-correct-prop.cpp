//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-correct-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      ???
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace correct {

VideoCorrectProp::VideoCorrectProp (const Acessor& _ph) :
  saturation_ (VideoCorrectProp::def),
  bright_ (VideoCorrectProp::def),
  contrast_ (VideoCorrectProp::def),
  sharp_ (VideoCorrectProp::def),
  hue_ (VideoCorrectProp::def),
  gamma_ (VideoCorrectProp::def),
  white_balance_ (VideoCorrectProp::def),
  adaptive_ (false),
  short2byte_ (true)
{
  property_name_ = gen_get_mid ();
}


VideoCorrectProp::~VideoCorrectProp ()
{}


::libs::events::IEvent::ptr
VideoCorrectProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<VideoCorrectProp> (this, _deep);
}


void
VideoCorrectProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<float> (_param, "saturation", saturation_);
      ::libs::icore::xml::helpers::load<float> (_param, "bright", bright_);
      ::libs::icore::xml::helpers::load<float> (_param, "contrast", contrast_);
      ::libs::icore::xml::helpers::load<float> (_param, "sharp", sharp_);
      ::libs::icore::xml::helpers::load<float> (_param, "hue", hue_);
      ::libs::icore::xml::helpers::load<float> (_param, "gamma", gamma_);
      ::libs::icore::xml::helpers::load<float> (_param, "white_balance", white_balance_);
      ::libs::icore::xml::helpers::load<bool> (_param, "adaptive", adaptive_);
      ::libs::icore::xml::helpers::load<bool> (_param, "short2byte", short2byte_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "id_impl", hint_impl_);

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoCorrectProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoCorrectProp);
  super::copy_int (_src);

  saturation_    = _dsrc->saturation_;
  bright_        = _dsrc->bright_;
  contrast_      = _dsrc->contrast_;
  sharp_         = _dsrc->sharp_;
  hue_           = _dsrc->hue_;
  gamma_         = _dsrc->gamma_;
  white_balance_ = _dsrc->white_balance_;
  adaptive_      = _dsrc->adaptive_;
  short2byte_    = _dsrc->short2byte_;
  hint_impl_     = _dsrc->hint_impl_;

  self_correct ();
  return;
}


template <class Archive>
void
VideoCorrectProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (saturation_);
  ar& BOOST_SERIALIZATION_NVP (bright_);
  ar& BOOST_SERIALIZATION_NVP (contrast_);
  ar& BOOST_SERIALIZATION_NVP (sharp_);
  ar& BOOST_SERIALIZATION_NVP (hue_);
  ar& BOOST_SERIALIZATION_NVP (gamma_);
  ar& BOOST_SERIALIZATION_NVP (white_balance_);
  ar& BOOST_SERIALIZATION_NVP (adaptive_);
  ar& BOOST_SERIALIZATION_NVP (short2byte_);
  ar& BOOST_SERIALIZATION_NVP (hint_impl_);

  self_correct ();
  return;
}


void
VideoCorrectProp::self_correct_int ()
{
  ::libs::helpers::utils::check_bound<float> (saturation_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (bright_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (contrast_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (sharp_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (hue_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (gamma_, VideoCorrectProp::min, VideoCorrectProp::max);
  ::libs::helpers::utils::check_bound<float> (white_balance_, VideoCorrectProp::min, VideoCorrectProp::max);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::correct

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::correct::VideoCorrectProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::correct::VideoCorrectProp);
