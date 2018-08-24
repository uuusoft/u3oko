//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-morphology-prop.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-morphology-prop.hpp"


namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {

TypeOperation
str2type_op (const std::string& _txt)
{
  static const std::pair<std::string, TypeOperation> _ops[] = {
    std::pair<std::string, TypeOperation> ("erosion", TypeOperation::erosion),
    std::pair<std::string, TypeOperation> ("dilation", TypeOperation::dilation),
    std::pair<std::string, TypeOperation> ("binary", TypeOperation::binary),
    std::pair<std::string, TypeOperation> ("skip", TypeOperation::empty)
  };

  for (const auto& _op : _ops)
    {
      if (_op.first == _txt)
        {
          return _op.second;
        }
    }

  //UASSERT_SIGNAL( "failed" );
  return TypeOperation::empty;
}


void
load_op (const base_functs::xml::itn& _prop, ParamsOperation& _info)
{
  pugi::xml_attribute _name_op = _prop->attribute ("name");

  if (!_name_op)
    {
      UASSERT_SIGNAL ("failed");
      return;
    }

  _info.type_ = str2type_op (_name_op.as_string ());

  if (pugi::xml_attribute _ext_name = _prop->attribute ("bound_filling"))
    {
      _info.bound_filling_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (0), UUU_ICAST_SHORT (255));
    }

  if (pugi::xml_attribute _ext_name = _prop->attribute ("val_filling"))
    {
      _info.val_filling_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (0), UUU_ICAST_SHORT (255));
    }

  if (pugi::xml_attribute _ext_name = _prop->attribute ("size_spot"))
    {
      _info.size_spot_ = ::libs::helpers::utils::ret_check_bound<short> (_ext_name.as_int (), UUU_ICAST_SHORT (1), UUU_ICAST_SHORT (9));
    }

  return;
}


VideoMorphologyProp::VideoMorphologyProp (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


VideoMorphologyProp::~VideoMorphologyProp ()
{}


::libs::events::IEvent::ptr
VideoMorphologyProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoMorphologyProp> (this, _deep);
}


void
VideoMorphologyProp::load_int (const base_functs::xml::itn& _prop)
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
          const off_buff_type _sindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_name_param.as_string ());
          const off_buff_type _dindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_val_param.as_string ());
          BuffInfo            _add;

          _add.bindx_diff_ = _dindx;

          base_functs::xml::ritn _ops = _param->children ("operation");
          base_functs::xml::itn  _op  = _ops.begin ();

          while (_op != _ops.end ())
            {
              _add.ops_.resize (_add.ops_.size () + 1);

              load_op (_op, _add.ops_.back ());

              ++_op;
            }

          diffs_.push_back (std::pair<off_buff_type, BuffInfo> (_sindx, _add));
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoMorphologyProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoMorphologyProp);
  super::copy_int (_src);
  diffs_ = _dsrc->diffs_;
  return;
}


template <class Archive>
void
VideoMorphologyProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (diffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
