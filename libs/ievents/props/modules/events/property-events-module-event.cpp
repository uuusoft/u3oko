//property-events-module-event.cpp
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
#include "property-events-module-event.hpp"

namespace libs { namespace ievents { namespace props { namespace modules { namespace events {

PropertyEventsModuleEvent::PropertyEventsModuleEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
  vals_.set (ValsEventsModule::max_count_events, 0);
  vals_.set (ValsEventsModule::max_size_database, 512);
}


PropertyEventsModuleEvent::~PropertyEventsModuleEvent ()
{}


PropertyEventsModuleEvent::value_type
PropertyEventsModuleEvent::get_val (const ValsEventsModule& _key) const
{
  return vals_.get (_key);
}


void
PropertyEventsModuleEvent::set_val (const ValsEventsModule& _key, value_type _val)
{
  vals_.set (_key, _val);
  return;
}


::libs::events::IEvent::ptr
PropertyEventsModuleEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<PropertyEventsModuleEvent> (this, _deep);
}


void
PropertyEventsModuleEvent::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      const std::string      _name_node = ::libs::icore::xml::helpers::get_node_name (_param);
      const ValsEventsModule _val       = str2val (_name_node);

      if (ValsEventsModule::no_val != _val)
        {
          PropertyEventsModuleEvent::value_type _raw_val = 0;
          if (::libs::icore::xml::helpers::load<PropertyEventsModuleEvent::value_type> (_param, _name_node, _raw_val))
            {
              vals_.set (_val, _raw_val);
            }
        }

      ++_param;
    }

  self_correct ();
  return;
}

#if 0
void
PropertyEventsModuleEvent::correct ()
{
  static const std::pair<ValsEventsModule, const PropertyEventsModuleEvent::bounds_type*> _ids[] = {
    { ValsEventsModule::max_cache_events, &consts::bounds_max_cache_events },
    { ValsEventsModule::ms_max_period_flush_events, &consts::bounds_ms_max_period_flush_events },
    { ValsEventsModule::max_size_one_log_file_byte, &consts::bounds_max_size_one_log_file_byte }
  };

  for (const auto& _id : _ids)
    {
      auto _val = vals_.get (_id.first);
      _val      = ::libs::helpers::utils::ret_check_bound<PropertyEventsModuleEvent::value_type> (_val, _id.second->first, _id.second->second);
      vals_.set (_id.first, _val);
    }

  return;
}
#endif

void
PropertyEventsModuleEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (PropertyEventsModuleEvent);
  super::copy_int (_src);
  vals_ = _dsrc->vals_;
  return;
}


template <class Archive>
void
PropertyEventsModuleEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (vals_);
  return;
}

}}}}}      // namespace libs::ievents::props::modules::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
