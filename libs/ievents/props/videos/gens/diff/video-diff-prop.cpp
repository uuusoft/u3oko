//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-diff-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-diff-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {

void
load_op (const base_functs::xml::itn& _prop, ParamsVideoDiffProp& _info)
{
  if (pugi::xml_attribute _ext_name = _prop->attribute ("enable"))
    {
      _info.enable_ = _ext_name.as_bool ();
    }

  if (pugi::xml_attribute _ext_name = _prop->attribute ("bound_filling"))
    {
      _info.bound_filling_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (0), UUU_ICAST_SHORT (255));
    }

  if (pugi::xml_attribute _ext_name = _prop->attribute ("val_filling"))
    {
      _info.val_filling_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (0), UUU_ICAST_SHORT (255));
    }

  return;
}


VideoDiffProp::VideoDiffProp (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
VideoDiffProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<VideoDiffProp> (this, _deep);
}


void
VideoDiffProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  diffs_.clear ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("sindx");
      pugi::xml_attribute _val_param  = _param->attribute ("dindx");

      if (_name_param && _val_param)
        {
          const off_buff_type   _sindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_name_param.as_string ());
          const off_buff_type   _dindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_val_param.as_string ());
          InfoBuffVideoDiffProp _add;

          _add.bindx_diff_ = _dindx;

          base_functs::xml::ritn _ops = _param->children ("operation");
          base_functs::xml::itn  _op  = _ops.begin ();


          if (_op != _ops.end ())
            {
              load_op (_op, _add.op_);
            }

          diffs_.push_back (std::pair<off_buff_type, InfoBuffVideoDiffProp> (_sindx, _add));
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoDiffProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoDiffProp);
  super::copy_int (_src);
  diffs_ = _dsrc->diffs_;
  return;
}


template <class Archive>
void
VideoDiffProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (diffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
