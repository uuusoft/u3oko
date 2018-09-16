//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-time-noise-remover-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-time-noise-remover-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace time {

VideoTimeNoiseRemoverProp::VideoTimeNoiseRemoverProp (const Acessor& _ph) :
  name_impl_ ("default"),
  dump_counter_frame_ (0),
  indx_diff_buff_ (utils::dbuffs::video::consts::offs::invalid)
{
  property_name_ = gen_get_mid ();
}


VideoTimeNoiseRemoverProp::~VideoTimeNoiseRemoverProp ()
{}


::libs::events::IEvent::ptr
VideoTimeNoiseRemoverProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<VideoTimeNoiseRemoverProp> (this, _deep);
}


void
VideoTimeNoiseRemoverProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  buffs_.clear ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<std::string> (_param, "name impl", name_impl_);
      ::libs::icore::xml::helpers::load<int> (_param, "dump_counter_frame", dump_counter_frame_);

      if (std::string ("indx_diff_buff") == _name_param.as_string ())
        {
          indx_diff_buff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_val_param.as_string ());
        }

      ::libs::icore::xml::helpers::load (
        _param,
        "indx_src_buff",
        [this](const std::string& _rval) {
          auto _sval = utils::dbuffs::video::consts::offs::str2eoffbuff (_rval);
          buffs_.push_back (_sval);
          return;
        });

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoTimeNoiseRemoverProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoTimeNoiseRemoverProp);
  super::copy_int (_src);
  name_impl_          = _dsrc->name_impl_;
  buffs_              = _dsrc->buffs_;
  dump_counter_frame_ = _dsrc->dump_counter_frame_;
  indx_diff_buff_     = _dsrc->indx_diff_buff_;
  impl_info_          = _dsrc->impl_info_;
  return;
}


template <class Archive>
void
VideoTimeNoiseRemoverProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);

  ar& BOOST_SERIALIZATION_NVP (name_impl_);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  ar& BOOST_SERIALIZATION_NVP (dump_counter_frame_);
  ar& BOOST_SERIALIZATION_NVP (indx_diff_buff_);
  ar& BOOST_SERIALIZATION_NVP (impl_info_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::noises::time

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
