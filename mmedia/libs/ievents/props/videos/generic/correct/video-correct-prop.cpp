/**
\file       video-correct-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"

namespace libs::ievents::props::videos::generic::correct
{
VideoCorrectProp::VideoCorrectProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoCorrectProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoCorrectProp > (this, deep);
}


void
VideoCorrectProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  saturation_             = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("saturation"));
  bright_                 = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("bright"));
  contrast_               = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("contrast"));
  sharp_                  = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("sharp"));
  hue_                    = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("hue"));
  gamma_                  = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("gamma"));
  white_balance_          = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("white_balance"));
  backlight_compensation_ = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("backlight_compensation"));
  gain_                   = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("gain"));
  exposure_               = ::boost::json::value_to< std::pair< float, bool > > (obj.at ("exposure"));
  adaptive_               = obj.at ("adaptive").as_bool ();
  short2byte_             = obj.at ("short2byte").as_bool ();
  hint_correct_impl_      = to_selector_impl_type (::libs::helpers::json::get_uint32 (obj.at ("hint_correct_impl")));
}


void
VideoCorrectProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["saturation"]             = ::boost::json::value_from (saturation_);
  obj["bright"]                 = ::boost::json::value_from (bright_);
  obj["contrast"]               = ::boost::json::value_from (contrast_);
  obj["sharp"]                  = ::boost::json::value_from (sharp_);
  obj["hue"]                    = ::boost::json::value_from (hue_);
  obj["gamma"]                  = ::boost::json::value_from (gamma_);
  obj["white_balance"]          = ::boost::json::value_from (white_balance_);
  obj["backlight_compensation"] = ::boost::json::value_from (backlight_compensation_);
  obj["gain"]                   = ::boost::json::value_from (gain_);
  obj["exposure"]               = ::boost::json::value_from (exposure_);
  obj["adaptive"]               = adaptive_;
  obj["short2byte"]             = short2byte_;
  obj["hint_correct_impl"]      = U3_CAST_UINT32_FORCE (hint_correct_impl_);
}


void
VideoCorrectProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoCorrectProp > (src);
  super::copy_int (src);

  saturation_             = dsrc->saturation_;
  bright_                 = dsrc->bright_;
  contrast_               = dsrc->contrast_;
  sharp_                  = dsrc->sharp_;
  hue_                    = dsrc->hue_;
  gamma_                  = dsrc->gamma_;
  white_balance_          = dsrc->white_balance_;
  exposure_               = dsrc->exposure_;
  backlight_compensation_ = dsrc->backlight_compensation_;
  gain_                   = dsrc->gain_;
  adaptive_               = dsrc->adaptive_;
  short2byte_             = dsrc->short2byte_;
  hint_correct_impl_      = dsrc->hint_correct_impl_;
}


template< class Archive >
void
VideoCorrectProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (saturation_);
  arh& BOOST_SERIALIZATION_NVP (bright_);
  arh& BOOST_SERIALIZATION_NVP (contrast_);
  arh& BOOST_SERIALIZATION_NVP (sharp_);
  arh& BOOST_SERIALIZATION_NVP (hue_);
  arh& BOOST_SERIALIZATION_NVP (gamma_);
  arh& BOOST_SERIALIZATION_NVP (white_balance_);
  arh& BOOST_SERIALIZATION_NVP (exposure_);
  arh& BOOST_SERIALIZATION_NVP (backlight_compensation_);
  arh& BOOST_SERIALIZATION_NVP (gain_);
  arh& BOOST_SERIALIZATION_NVP (adaptive_);
  arh& BOOST_SERIALIZATION_NVP (short2byte_);
  arh& BOOST_SERIALIZATION_NVP (hint_correct_impl_);

  self_correct ();
}


void
VideoCorrectProp::self_correct_int ()
{
  ::libs::helpers::utils::check_bound< float > (saturation_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (bright_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (contrast_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (sharp_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (hue_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (gamma_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (white_balance_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (backlight_compensation_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (gain_.first, consts::min, consts::max);
  ::libs::helpers::utils::check_bound< float > (exposure_.first, consts::min, consts::max);
}
}   // namespace libs::ievents::props::videos::generic::correct

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::correct::VideoCorrectProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::correct::VideoCorrectProp);
