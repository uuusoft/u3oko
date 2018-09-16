//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       application-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "application-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace application {

ApplicationProp::ApplicationProp (const Acessor& _ph) :
  single_process_ (true),
  messenger_impl_ ("fast"),
  min_log_filter_ ("trace")
{
  property_name_ = gen_get_mid ();
}


ApplicationProp::~ApplicationProp ()
{}


bool
ApplicationProp::is_single_process () const
{
  return single_process_;
}


const std::string&
ApplicationProp::get_messenger_impl () const
{
  return messenger_impl_;
}


const ApplicationProp::xml_paths_type&
ApplicationProp::get_xml_paths () const
{
  return xml_data_paths_;
}


::libs::events::IEvent::ptr
ApplicationProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ApplicationProp> (this, _deep);
}


void
ApplicationProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      ::libs::icore::xml::helpers::load<bool> (_param, "single process", single_process_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "intersubsys", messenger_impl_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "min_log_filter", min_log_filter_);

      if ("xml-data-path" == ::libs::icore::xml::helpers::get_node_name (_param))
        {
          xml_data_paths_.push_back ("");
          ::libs::icore::xml::helpers::load<std::string> (_param, "xml-data-path", xml_data_paths_.back ());
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
ApplicationProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ApplicationProp);
  super::copy_int (_src);
  single_process_ = _dsrc->single_process_;
  messenger_impl_ = _dsrc->messenger_impl_;
  min_log_filter_ = _dsrc->min_log_filter_;
  xml_data_paths_ = _dsrc->xml_data_paths_;
  return;
}


template <class Archive>
void
ApplicationProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (single_process_);
  ar& BOOST_SERIALIZATION_NVP (messenger_impl_);
  ar& BOOST_SERIALIZATION_NVP (min_log_filter_);
  ar& BOOST_SERIALIZATION_NVP (xml_data_paths_);
  return;
}

}}}}      // namespace libs::ievents::props::application

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::application::ApplicationProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::application::ApplicationProp);
