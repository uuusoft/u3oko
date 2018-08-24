//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-histogram-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-histogram-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace histogram {

VideoHistogramProp::VideoHistogramProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


VideoHistogramProp::~VideoHistogramProp ()
{}


::libs::events::IEvent::ptr
VideoHistogramProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoHistogramProp> (this, _deep);
}


void
VideoHistogramProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute    _name_param = _param->attribute ("name");
      pugi::xml_attribute    _val_param  = _param->attribute ("val");
      base_functs::xml::ritn _layers     = _prop->children ("layer");
      base_functs::xml::itn  _layer      = _layers.begin ();

      while (_layer != _layers.end ())
        {
          pugi::xml_attribute _aindx = _layer->attribute ("indx");

          if (_aindx)
            {
              const off_buff_type _bindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_aindx.as_string ());      //, 0, utils::dbuffs::video::consts::offs::count_buffs - 1 );
              BuffEventInfo       _add;

              if (pugi::xml_attribute _aval_norm = _layer->attribute ("norm"))
                {
                  _add.norm_ = _aval_norm.as_bool ();
                }

              if (pugi::xml_attribute _aval_dest = _layer->attribute ("dest"))
                {
                  _add.dindx_ = _aval_dest.as_int ();
                }

              buffs2norm_.push_back (std::pair<off_buff_type, BuffEventInfo> (_bindx, _add));
            }

          ++_layer;
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoHistogramProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoHistogramProp);
  super::copy_int (_src);
  buffs2norm_ = _dsrc->buffs2norm_;
  return;
}


template <class Archive>
void
VideoHistogramProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buffs2norm_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::histogram

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::histogram::VideoHistogramProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::histogram::VideoHistogramProp);
