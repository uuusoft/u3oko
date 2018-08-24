//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       freq-video-noise-remover-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "freq-video-noise-remover-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace freq {

FreqVideoNoiseRemoverProp::FreqVideoNoiseRemoverProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


FreqVideoNoiseRemoverProp::~FreqVideoNoiseRemoverProp ()
{}


::libs::events::IEvent::ptr
FreqVideoNoiseRemoverProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<FreqVideoNoiseRemoverProp> (this, _deep);
}


void
FreqVideoNoiseRemoverProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("sindx");
      pugi::xml_attribute _val_param  = _param->attribute ("dindx");

      if (_name_param && _val_param)
        {
          const off_buff_type      _sindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_name_param.as_string ());
          const off_buff_type      _dindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_val_param.as_string ());
          InfoBuffFreqNoiseRemover _add;

          _add.bindx_diff_ = _dindx;

          if (pugi::xml_attribute _ext_name = _param->attribute ("bound_x_plus_y"))
            {
              _add.bound_x_plus_y_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (0), UUU_ICAST_SHORT (16));
            }

          if (pugi::xml_attribute _ext_name = _param->attribute ("dwt_koeff2"))
            {
              _add.dwt_koeff2_ = _ext_name.as_float ();
            }

          buffs_.push_back (std::pair<::utils::dbuffs::video::consts::offs::off_buff_type, InfoBuffFreqNoiseRemover> (_sindx, _add));
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
FreqVideoNoiseRemoverProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (FreqVideoNoiseRemoverProp);
  super::copy_int (_src);
  buffs_ = _dsrc->buffs_;
  return;
}


template <class Archive>
void
FreqVideoNoiseRemoverProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
