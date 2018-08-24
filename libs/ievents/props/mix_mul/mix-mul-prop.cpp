//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mix-mul-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "mix-mul-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace mix_mul {

MixMulProp::MixMulProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


MixMulProp::~MixMulProp ()
{}


::libs::events::IEvent::ptr
MixMulProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<MixMulProp> (this, _deep);
}


void
MixMulProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _outs = _prop->children ("out");
  base_functs::xml::itn  _out  = _outs.begin ();

  while (_out != _outs.end ())
    {
      pugi::xml_attribute _indx_layer = _out->attribute ("indx");

      if (_indx_layer)
        {
          const int _indx = ::libs::helpers::utils::ret_check_bound<int> (_indx_layer.as_int (), 0, outs_.size () - 1);

          load_out (_out, &outs_[_indx]);
        }

      ++_out;
    }

  self_correct ();
  return;
}


void
MixMulProp::load_out (const base_functs::xml::itn& _node, OutChannelInfo* _prop)
{
  UASSERT (_prop);

  base_functs::xml::ritn _params = _node->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  _prop->srcs2dsts_.clear ();
  _prop->srcs2dsts_.reserve (16);

  while (_param != _params.end ())
    {
      ::libs::events::buff::BuffEventInfo _add;

      _add.load (_param);
      _prop->srcs2dsts_.push_back (_add);

      ++_param;
    }

  return;
}


void
MixMulProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MixMulProp);
  super::copy_int (_src);
  outs_ = _dsrc->outs_;
  return;
}


template <class Archive>
void
MixMulProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (outs_);
  return;
}

}}}}      // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::mix_mul::MixMulProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::mix_mul::MixMulProp);
