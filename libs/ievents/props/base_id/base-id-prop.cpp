//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-id-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       18.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "base-id-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace base_id {

BaseIdProp::BaseIdProp (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


BaseIdProp::~BaseIdProp ()
{}


::libs::events::IEvent::ptr
BaseIdProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseIdProp> (this, _deep);
}


void
BaseIdProp::load_int (const base_functs::xml::itn& _prop)
{
  XULOG_TRACE ("BaseIdProp::load_int: beg");
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      ::libs::icore::xml::helpers::load<source_name_type> (_param, "source_name", source_name_);

      const std::string _name_param = _param->attribute ("name").as_string ();
      XULOG_TRACE ("BaseIdProp::load_int: name_param=" << _name_param);

      if (std::string ("buff2module") == _name_param)
        {
          buff2modules_.push_back (Buff2ModuleInfo ());
          load_buff2module (_param, &buff2modules_.back ());
        }

      ++_param;
    }

  self_correct ();
  XULOG_TRACE ("BaseIdProp::load_int: end");
  return;
}


void
BaseIdProp::load_buff2module (const base_functs::xml::itn& _node, Buff2ModuleInfo* _prop)
{
  XULOG_TRACE ("BaseIdProp::load_buff2module: beg");
  UASSERT (_prop);
  pugi::xml_attribute _nfps       = _node->attribute ("fps");
  pugi::xml_attribute _nindx_buff = _node->attribute ("indx_buff");
  pugi::xml_attribute _nmodule    = _node->attribute ("module");

  if (!_nfps || !_nindx_buff || !_nmodule)
    {
      XULOG_WARNING ("BaseIdProp::load_buff2module: skip load, empty attributes,  " << _nfps << ", " << _nindx_buff << ", " << _nmodule);
      return;
    }

  _prop->indx_buff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_nindx_buff.as_string ());
  _prop->fps_       = _nfps.as_float ();
  _prop->module_    = _nmodule.as_string ();
  XULOG_TRACE ("BaseIdProp::load_buff2module: load, indx=" << _prop->indx_buff_ << ", fps=" << _prop->fps_ << ", module=" << _prop->module_);
  XULOG_TRACE ("BaseIdProp::load_buff2module: end");
  return;
}


void
BaseIdProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseIdProp);
  super::copy_int (_src);
  source_name_  = _dsrc->source_name_;
  buff2modules_ = _dsrc->buff2modules_;
  return;
}


template <class Archive>
void
BaseIdProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (source_name_);
  ar& BOOST_SERIALIZATION_NVP (buff2modules_);
  return;
}

}}}}      // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::base_id::BaseIdProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::base_id::BaseIdProp);
