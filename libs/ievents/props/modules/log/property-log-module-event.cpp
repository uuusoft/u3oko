//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       property-log-module-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "property-log-module-event.hpp"

namespace libs { namespace ievents { namespace props { namespace modules { namespace log { namespace consts {

const PropertyLogModuleEvent::bounds_type bounds_max_cache_events (0, 16 * 1024);                       //< ???
const PropertyLogModuleEvent::bounds_type bounds_ms_max_period_flush_events (0, 15 * 60 * 1000);        //< ???
const PropertyLogModuleEvent::bounds_type bounds_max_size_one_log_file_byte (0, 10 * 1024 * 1024);      //< ???

}}}}}}      // namespace libs::ievents::props::modules::log::consts

namespace libs { namespace ievents { namespace props { namespace modules { namespace log {

PropertyLogModuleEvent::PropertyLogModuleEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();

  vals_.set (ValsLogModule::max_cache_events, 16);
  vals_.set (ValsLogModule::ms_max_period_flush_events, 60 * 1000);
  vals_.set (ValsLogModule::max_size_one_log_file_byte, 1024 * 1024);
  vals_.set (ValsLogModule::enable_store_call_place, 0);
}


PropertyLogModuleEvent::~PropertyLogModuleEvent ()
{}


PropertyLogModuleEvent::value_type
PropertyLogModuleEvent::get_val (const ValsLogModule& _key) const
{
  return vals_.get (_key);
}


void
PropertyLogModuleEvent::set_val (const ValsLogModule& _key, value_type _val)
{
  vals_.set (_key, _val);
  return;
}


::libs::events::IEvent::ptr
PropertyLogModuleEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<PropertyLogModuleEvent> (this, _deep);
}


void
PropertyLogModuleEvent::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      const std::string   _name_node = ::libs::icore::xml::helpers::get_node_name (_param);
      const ValsLogModule _val       = str2val (_name_node);

      if (ValsLogModule::no_val != _val)
        {
          PropertyLogModuleEvent::value_type _raw_val = 0;
          if (::libs::icore::xml::helpers::load<PropertyLogModuleEvent::value_type> (_param, _name_node, _raw_val))
            {
              vals_.set (_val, _raw_val);
            }
        }

      ++_param;
    }

  correct ();
  self_correct ();
  return;
}


void
PropertyLogModuleEvent::correct ()
{
  static const std::pair<ValsLogModule, const PropertyLogModuleEvent::bounds_type*> _ids[] = {
    { ValsLogModule::max_cache_events, &consts::bounds_max_cache_events },
    { ValsLogModule::ms_max_period_flush_events, &consts::bounds_ms_max_period_flush_events },
    { ValsLogModule::max_size_one_log_file_byte, &consts::bounds_max_size_one_log_file_byte }
  };

  for (const auto& _id : _ids)
    {
      auto _val = vals_.get (_id.first);
      _val      = ::libs::helpers::utils::ret_check_bound<PropertyLogModuleEvent::value_type> (_val, _id.second->first, _id.second->second);
      vals_.set (_id.first, _val);
    }

  return;
}


void
PropertyLogModuleEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (PropertyLogModuleEvent);
  super::copy_int (_src);
  vals_ = _dsrc->vals_;
  return;
}


template <class Archive>
void
PropertyLogModuleEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (vals_);
  return;
}

}}}}}      // namespace libs::ievents::props::modules::log

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
