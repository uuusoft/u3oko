//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       Vec2ImageProp.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "vec2image-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace vec2image {

Vec2ImageProp::Vec2ImageProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


::libs::events::IEvent::ptr
Vec2ImageProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<Vec2ImageProp> (this, _deep);
}


void
Vec2ImageProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  buffs_.clear ();
  buffs_.reserve (16);

  while (_param != _params.end ())
    {
      BuffEventInfoVec2Image1 _add;
      _add.load (_param);
      buffs_.push_back (_add);
      ++_param;
    }

  self_correct ();
  return;
}


void
Vec2ImageProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (Vec2ImageProp);
  super::copy_int (_src);
  buffs_ = _dsrc->buffs_;
  return;
}


template <class Archive>
void
Vec2ImageProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::vec2image::Vec2ImageProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::vec2image::Vec2ImageProp);
