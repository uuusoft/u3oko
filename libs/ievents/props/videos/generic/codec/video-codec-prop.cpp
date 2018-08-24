//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-codec-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-codec-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace codec {

TypeCodecMode
str2mode_codec (const std::string& _str)
{
  TypeCodecMode _ret = TypeCodecMode::coder;

  if ("decoder" == _str)
    {
      _ret = TypeCodecMode::decoder;
    }
  return _ret;
}


OverrideCodecDataType
str2write_strategy (const std::string& _str)
{
  if (_str == "allways_write")
    {
      return OverrideCodecDataType::allways_write;
    }
  if (_str == "write_if_not_empty")
    {
      return OverrideCodecDataType::write_if_not_empty;
    }
  if (_str == "write_if_empty")
    {
      return OverrideCodecDataType::write_if_empty;
    }

  XULOG_WARNING ("unknown write strategy codec, " << _str);
  return OverrideCodecDataType::allways_write;
}


VideoCodecProp::VideoCodecProp (const Acessor& _ph) :
  dump_counter_frame_ (0),
  dump_compressed_to_file_ (false),
  fps_coder_ (0),
  buffs_ (::utils::dbuffs::video::consts::offs::raw, ::utils::dbuffs::video::consts::offs::mjpg),
  write_codec_strategy_ (OverrideCodecDataType::allways_write),
  decode_mirror_y_ (false),
  code_mirror_y_ (false)
{
  property_name_ = gen_get_type_text_id ();
}


VideoCodecProp::~VideoCodecProp ()
{}


void
VideoCodecProp::correct ()
{
  plane_.correct ();
  return;
}


void
VideoCodecProp::reset ()
{
  name_idll_.clear ();
  plane_.reset ();
  return;
}


::libs::events::IEvent::ptr
VideoCodecProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoCodecProp> (this, _deep);
}


void
VideoCodecProp::load_int (const base_functs::xml::itn& _prop)
{
  reset ();

  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load (
        _param,
        "type",
        [this](const std::string& _val) {
          this->plane_.type_ = str2mode_codec (_val);
          return;
        });

      ::libs::icore::xml::helpers::load (
        _param,
        "write_codec_strategy",
        [this](const std::string& _val) {
          this->write_codec_strategy_ = str2write_strategy (_val);
          return;
        });

      ::libs::icore::xml::helpers::load<std::string> (_param, "name_ext_dll", name_idll_);
      ::libs::icore::xml::helpers::load<bool> (_param, "dump_compressed_to_file", dump_compressed_to_file_);
      ::libs::icore::xml::helpers::load<int> (_param, "quality", plane_.quality_);
      ::libs::icore::xml::helpers::load<bool> (_param, "decode_mirror_y", decode_mirror_y_);
      ::libs::icore::xml::helpers::load<bool> (_param, "code_mirror_y", code_mirror_y_);
      ::libs::icore::xml::helpers::load<unsigned long long> (_param, "dump_counter_frame", dump_counter_frame_);
      ::libs::icore::xml::helpers::load<int> (_param, "fps_coder", fps_coder_);

      ::libs::icore::xml::helpers::load<float> (_param, "max_percent_pframe", plane_.max_percent_pframe_);
      ::libs::icore::xml::helpers::load<int> (_param, "max_period_key_frame", plane_.max_period_kframe_);
      ::libs::icore::xml::helpers::load<float> (_param, "percent_block", plane_.percent_block_);
      ::libs::icore::xml::helpers::load<bool> (_param, "monochrome", plane_.monochrome_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "hint_impl", hint_impl_);

      ::libs::helpers::utils::check_bound<int> (plane_.quality_, 1, 100);
      ::libs::helpers::utils::check_bound (plane_.max_percent_pframe_, 0.0f, 100.0f);
      ::libs::helpers::utils::check_bound<int> (plane_.max_period_kframe_, 1, 2000);
      ::libs::helpers::utils::check_bound (plane_.percent_block_, 0.0f, 100.0f);

      ::libs::helpers::utils::check_bound<int> (fps_coder_, 0, 1000);

      if (std::string ("eentropy") == _name_param.as_string ())
        {
          std::string              _all_valls = _val_param.as_string ();
          std::vector<std::string> _vals;

          boost::algorithm::split (_vals, _all_valls, boost::is_any_of (","));

          const std::size_t _ecount = std::min<std::size_t> (_vals.size (), consts::max_count_entropy_coders);
          for (std::size_t _eindx = 0; _eindx < _ecount; ++_eindx)
            {
              _vals[_eindx].copy (plane_.entropy_coders_[_eindx], consts::max_len_name_entropy_coder);
            }
        }

      ++_param;
    }

  {
    base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
    base_functs::xml::itn  _param  = _params.begin ();

    while (_param != _params.end ())
      {
        buffs_.load (_param);
        buffs_.check (true, false);
        ++_param;
      }
  }

  correct ();
  self_correct ();
  return;
}


void
VideoCodecProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoCodecProp);
  super::copy_int (_src);

  name_idll_               = _dsrc->name_idll_;
  dump_counter_frame_      = _dsrc->dump_counter_frame_;
  plane_                   = _dsrc->plane_;
  dump_compressed_to_file_ = _dsrc->dump_compressed_to_file_;
  hint_impl_               = _dsrc->hint_impl_;
  fps_coder_               = _dsrc->fps_coder_;
  buffs_                   = _dsrc->buffs_;
  write_codec_strategy_    = _dsrc->write_codec_strategy_;
  decode_mirror_y_         = _dsrc->decode_mirror_y_;
  code_mirror_y_           = _dsrc->code_mirror_y_;
  return;
}


template <class Archive>
void
VideoCodecProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);

  ar& BOOST_SERIALIZATION_NVP (name_idll_);
  ar& BOOST_SERIALIZATION_NVP (dump_compressed_to_file_);
  ar& BOOST_SERIALIZATION_NVP (plane_.type_);
  ar& BOOST_SERIALIZATION_NVP (plane_.quality_);
  ar& BOOST_SERIALIZATION_NVP (plane_.max_percent_pframe_);
  ar& BOOST_SERIALIZATION_NVP (plane_.max_period_kframe_);
  ar& BOOST_SERIALIZATION_NVP (plane_.percent_block_);
  ar& BOOST_SERIALIZATION_NVP (plane_.monochrome_);
  ar& BOOST_SERIALIZATION_NVP (plane_.entropy_coders_);
  ar& BOOST_SERIALIZATION_NVP (dump_counter_frame_);
  ar& BOOST_SERIALIZATION_NVP (hint_impl_);
  ar& BOOST_SERIALIZATION_NVP (fps_coder_);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  ar& BOOST_SERIALIZATION_NVP (write_codec_strategy_);
  ar& BOOST_SERIALIZATION_NVP (decode_mirror_y_);
  ar& BOOST_SERIALIZATION_NVP (code_mirror_y_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::codec

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::codec::VideoCodecProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::codec::VideoCodecProp);
