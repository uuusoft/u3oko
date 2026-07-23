/**
\file       video-codec-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-codec-prop.hpp"

namespace libs::events_base::props::videos::generic::codec
{
auto
str2mode_codec (const std::string& str) -> CodecModes
{
  CodecModes ret = CodecModes::coder;

  if ("decoder" == str)
  {
    ret = CodecModes::decoder;
  }
  return ret;
}


auto
str2write_strategy (const std::string& str) -> Writes
{
  if (str == "allways_write")
  {
    return Writes::allways_write;
  }
  if (str == "write_if_not_empty")
  {
    return Writes::write_if_not_empty;
  }
  if (str == "write_if_empty")
  {
    return Writes::write_if_empty;
  }
  U3_XLOG_WARN ("unknown write strategy codec" + TOLOG (str));
  return Writes::allways_write;
}


VideoCodecProp::VideoCodecProp (const Acessor& pha)
{
  state_ = events::PropertyUsings::enabled;
}


auto
VideoCodecProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoCodecProp::gen_get_mid ();
}


void
VideoCodecProp::correct ()
{
  plane_.correct ();
}


void
VideoCodecProp::reset ()
{
  preferred_impl_.clear ();
  plane_.reset ();
}


auto
VideoCodecProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoCodecProp > (this, deep);
}


void
VideoCodecProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  max_period_ic_frame_  = ::libs::utility::json::get_uint32 (obj.at ("max_period_ic_frame"));
  fps_coder_            = ::libs::utility::json::get_uint32 (obj.at ("fps_coder"));
  plane_                = ::boost::json::value_to< VideoCodecFlatProp > (obj.at ("plane"));
  preferred_impl_       = obj.at ("preferred_impl").as_string ();
  bufs_                 = ::boost::json::value_to< syn::EventBufs > (obj.at ("evbufs"));
  dump_frame_counter_   = ::libs::utility::json::get_uint64 (obj.at ("dump_counter_frame"));
  dump_result2file_     = obj.at ("dump_compressed_to_file").as_bool ();
  write_codec_strategy_ = ::boost::json::value_to< Writes > (obj.at ("write_codec_strategy"));
  decode_flip_y_        = obj.at ("decode_flip_y").as_bool ();
  code_flip_y_          = obj.at ("code_flip_y").as_bool ();
  hint_codec_impl_      = ::boost::json::value_to< ::libs::events_base::SelectorImpls > (obj.at ("hint_codec_impl"));
}


void
VideoCodecProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["max_period_ic_frame"]     = max_period_ic_frame_;
  obj["fps_coder"]               = fps_coder_;
  obj["plane"]                   = boost::json::value_from (plane_);
  obj["preferred_impl"]          = preferred_impl_;
  obj["evbufs"]                  = boost::json::value_from (bufs_);
  obj["dump_counter_frame"]      = dump_frame_counter_;
  obj["dump_compressed_to_file"] = dump_result2file_;
  obj["write_codec_strategy"]    = ::boost::json::value_from (write_codec_strategy_);
  obj["decode_flip_y"]           = decode_flip_y_;
  obj["code_flip_y"]             = code_flip_y_;
  obj["hint_codec_impl"]         = ::boost::json::value_from (hint_codec_impl_);
}


void
VideoCodecProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoCodecProp > (src);
  super::copy_int (src);

  preferred_impl_       = dsrc->preferred_impl_;
  dump_frame_counter_   = dsrc->dump_frame_counter_;
  plane_                = dsrc->plane_;
  dump_result2file_     = dsrc->dump_result2file_;
  fps_coder_            = dsrc->fps_coder_;
  bufs_                 = dsrc->bufs_;
  write_codec_strategy_ = dsrc->write_codec_strategy_;
  decode_flip_y_        = dsrc->decode_flip_y_;
  code_flip_y_          = dsrc->code_flip_y_;
  hint_codec_impl_      = dsrc->hint_codec_impl_;
}


template< class Archive >
void
VideoCodecProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (preferred_impl_);
  arh& BOOST_SERIALIZATION_NVP (dump_result2file_);
  arh& BOOST_SERIALIZATION_NVP (plane_.type_);
  arh& BOOST_SERIALIZATION_NVP (plane_.quality_);
  arh& BOOST_SERIALIZATION_NVP (plane_.max_percent_pframe_);
  arh& BOOST_SERIALIZATION_NVP (plane_.max_period_kframe_);
  arh& BOOST_SERIALIZATION_NVP (plane_.percent_block_);
  arh& BOOST_SERIALIZATION_NVP (plane_.nocolor_);
  arh& BOOST_SERIALIZATION_NVP (dump_frame_counter_);
  arh& BOOST_SERIALIZATION_NVP (fps_coder_);
  arh& BOOST_SERIALIZATION_NVP (bufs_);
  arh& BOOST_SERIALIZATION_NVP (write_codec_strategy_);
  arh& BOOST_SERIALIZATION_NVP (decode_flip_y_);
  arh& BOOST_SERIALIZATION_NVP (code_flip_y_);
  arh& BOOST_SERIALIZATION_NVP (hint_codec_impl_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::codec

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::codec::VideoCodecProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::codec::VideoCodecProp);
