//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-scaler-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-scaler-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace scaler {

VideoScalerProp::VideoScalerProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


VideoScalerProp::~VideoScalerProp ()
{}


const std::vector<BuffEventInfoVideoScaler>&
VideoScalerProp::get_buffs () const
{
  return buffs_;
}


::libs::events::IEvent::ptr
VideoScalerProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoScalerProp> (this, _deep);
}


void
VideoScalerProp::load_int (const base_functs::xml::itn& _prop)
{
  ::libs::ievents::Event::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  buffs_.clear ();
  buffs_.reserve (16);


  while (_param != _params.end ())
    {
      BuffEventInfoVideoScaler _add;

      _add.load (_param);

      buffs_.push_back (_add);

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoScalerProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoScalerProp);
  super::copy_int (_src);
  buffs_ = _dsrc->buffs_;
  return;
}


template <class Archive>
void
VideoScalerProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::scaler

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::scaler::VideoScalerProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::scaler::VideoScalerProp);
