/**
\file       video-codec-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-codec-prop.hpp"

namespace libs::ievents::props::videos::generic::codec
{
CodecModes
str2mode_codec (const std::string& str)
{
  CodecModes ret = CodecModes::coder;

  if ("decoder" == str)
  {
    ret = CodecModes::decoder;
  }
  return ret;
}


Writes
str2write_strategy (const std::string& str)
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
  property_name_ = gen_get_mid ();
}


void
VideoCodecProp::correct ()
{
  plane_.correct ();
}


void
VideoCodecProp::reset ()
{
  dll_name_.clear ();
  plane_.reset ();
}


::libs::events::IEvent::ptr
VideoCodecProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoCodecProp > (this, deep);
}


void
VideoCodecProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  max_period_ic_frame_  = ::libs::helpers::json::get_uint32 (obj.at ("max_period_ic_frame"));
  fps_coder_            = ::libs::helpers::json::get_uint32 (obj.at ("fps_coder"));
  plane_                = ::boost::json::value_to< VideoCodecFlatProp > (obj.at ("plane"));
  dll_name_             = obj.at ("name_idll").as_string ();
  bufs_                 = ::boost::json::value_to< ::libs::events::buf::EventBufsInfo > (obj.at ("evbufs"));
  dump_counter_frame_   = ::libs::helpers::json::get_uint64 (obj.at ("dump_counter_frame"));
  dump_result2file_     = obj.at ("dump_compressed_to_file").as_bool ();
  write_codec_strategy_ = ::boost::json::value_to< Writes > (obj.at ("write_codec_strategy"));
  decode_flip_y_        = obj.at ("decode_flip_y").as_bool ();
  code_flip_y_          = obj.at ("code_flip_y").as_bool ();
  hint_codec_impl_      = ::boost::json::value_to< ::libs::ievents::SelectorImpls > (obj.at ("hint_codec_impl"));
}


void
VideoCodecProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["max_period_ic_frame"]     = max_period_ic_frame_;
  obj["fps_coder"]               = fps_coder_;
  obj["plane"]                   = boost::json::value_from (plane_);
  obj["name_idll"]               = dll_name_;
  obj["evbufs"]                  = boost::json::value_from (bufs_);
  obj["dump_counter_frame"]      = dump_counter_frame_;
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

  dll_name_             = dsrc->dll_name_;
  dump_counter_frame_   = dsrc->dump_counter_frame_;
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (dll_name_);
  arh& BOOST_SERIALIZATION_NVP (dump_result2file_);
  arh& BOOST_SERIALIZATION_NVP (plane_.type_);
  arh& BOOST_SERIALIZATION_NVP (plane_.quality_);
  arh& BOOST_SERIALIZATION_NVP (plane_.max_percent_pframe_);
  arh& BOOST_SERIALIZATION_NVP (plane_.max_period_kframe_);
  arh& BOOST_SERIALIZATION_NVP (plane_.percent_block_);
  arh& BOOST_SERIALIZATION_NVP (plane_.nocolor_);
  arh& BOOST_SERIALIZATION_NVP (dump_counter_frame_);
  arh& BOOST_SERIALIZATION_NVP (fps_coder_);
  arh& BOOST_SERIALIZATION_NVP (bufs_);
  arh& BOOST_SERIALIZATION_NVP (write_codec_strategy_);
  arh& BOOST_SERIALIZATION_NVP (decode_flip_y_);
  arh& BOOST_SERIALIZATION_NVP (code_flip_y_);
  arh& BOOST_SERIALIZATION_NVP (hint_codec_impl_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::codec

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::codec::VideoCodecProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::codec::VideoCodecProp);
