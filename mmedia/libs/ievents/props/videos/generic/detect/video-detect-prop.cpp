/**
\file       video-detect-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-detect-prop.hpp"

namespace libs::ievents::props::videos::generic::detect
{
VideoDetectProp::VideoDetectProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoDetectProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoDetectProp > (this, deep);
}


void
VideoDetectProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  mode_                 = obj.at ("mode").as_string ();
  bound_                = ::libs::helpers::json::get_int32 (obj.at ("bound"));
  size_core_morph_op_   = ::libs::helpers::json::get_int32 (obj.at ("size_core_morph_op"));
  id_morph_op_          = obj.at ("id_morph_op").as_string ();
  counter_morph_op_     = ::libs::helpers::json::get_int32 (obj.at ("counter_morph_op"));
  min_size_spot_        = ::libs::helpers::json::get_int32 (obj.at ("min_size_spot"));
  max_size_spot_        = ::libs::helpers::json::get_int32 (obj.at ("max_size_spot"));
  bufs_                 = ::boost::json::value_to< ::libs::events::buf::EventBufsInfo > (obj.at ("evbufs"));
  time_after_last_move_ = ::libs::helpers::json::get_int32 (obj.at ("time_after_last_move"));
  lazy_optim_           = obj.at ("lazy_optim").as_bool ();
  time_id_              = ::libs::helpers::json::get_int32 (obj.at ("time_id"));
  zone_id_              = ::libs::helpers::json::get_int32 (obj.at ("zone_id"));
  hint_detector_impl_   = ::boost::json::value_to< SelectorImpls > (obj.at ("hint_detector_impl"));
}


void
VideoDetectProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["mode"]                 = mode_;
  obj["bound"]                = bound_;
  obj["size_core_morph_op"]   = size_core_morph_op_;
  obj["id_morph_op"]          = id_morph_op_;
  obj["counter_morph_op"]     = counter_morph_op_;
  obj["min_size_spot"]        = min_size_spot_;
  obj["max_size_spot"]        = max_size_spot_;
  obj["evbufs"]               = ::boost::json::value_from (bufs_);
  obj["time_after_last_move"] = time_after_last_move_;
  obj["lazy_optim"]           = lazy_optim_;
  obj["time_id"]              = time_id_;
  obj["zone_id"]              = zone_id_;
  obj["hint_detector_impl"]   = ::boost::json::value_from (hint_detector_impl_);
}


void
VideoDetectProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoDetectProp > (src);
  super::copy_int (src);

  time_id_              = dsrc->time_id_;
  mode_                 = dsrc->mode_;
  zone_id_              = dsrc->zone_id_;
  bound_                = dsrc->bound_;
  bufs_                 = dsrc->bufs_;
  time_after_last_move_ = dsrc->time_after_last_move_;
  lazy_optim_           = dsrc->lazy_optim_;
  min_size_spot_        = dsrc->min_size_spot_;
  max_size_spot_        = dsrc->max_size_spot_;
  size_core_morph_op_   = dsrc->size_core_morph_op_;
  id_morph_op_          = dsrc->id_morph_op_;
  counter_morph_op_     = dsrc->counter_morph_op_;
  hint_detector_impl_   = dsrc->hint_detector_impl_;
}


void
VideoDetectProp::self_correct_int ()
{
  ::libs::helpers::utils::check_bound< std::int32_t > (bound_, 1, 255);
  ::libs::helpers::utils::check_bound< std::int32_t > (size_core_morph_op_, 3, 11);
  ::libs::helpers::utils::check_bound< std::int32_t > (counter_morph_op_, 0, 5);
  ::libs::helpers::utils::check_bound< std::int32_t > (min_size_spot_, 0, 100);
  ::libs::helpers::utils::check_bound< std::int32_t > (max_size_spot_, 0, 1000);
  ::libs::helpers::utils::check_bound< std::int32_t > (time_after_last_move_, 1, 60);
}


template< class Archive >
void
VideoDetectProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (time_id_);
  arh& BOOST_SERIALIZATION_NVP (mode_);
  arh& BOOST_SERIALIZATION_NVP (zone_id_);
  arh& BOOST_SERIALIZATION_NVP (bound_);
  arh& BOOST_SERIALIZATION_NVP (bufs_);
  arh& BOOST_SERIALIZATION_NVP (time_after_last_move_);
  arh& BOOST_SERIALIZATION_NVP (lazy_optim_);
  arh& BOOST_SERIALIZATION_NVP (min_size_spot_);
  arh& BOOST_SERIALIZATION_NVP (max_size_spot_);
  arh& BOOST_SERIALIZATION_NVP (size_core_morph_op_);
  arh& BOOST_SERIALIZATION_NVP (id_morph_op_);
  arh& BOOST_SERIALIZATION_NVP (counter_morph_op_);
  arh& BOOST_SERIALIZATION_NVP (hint_detector_impl_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::detect

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::detect::VideoDetectProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::detect::VideoDetectProp);
