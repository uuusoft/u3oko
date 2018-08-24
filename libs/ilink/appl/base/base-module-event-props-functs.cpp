//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-module-event-props-functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "base-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace base {

void
BaseModule::load_events_props ()
{
  const std::string             _name ("appl.xml");
  pugi::xml_document            _xml_doc;
  ::libs::icore::xml::TInitInfo _helper_info (std::const_pointer_cast<const ::libs::iproperties::appl_paths::IAppPaths> (paths_));
  ::libs::icore::xml::Loader    _helper_xml (_helper_info);

  event_props_.init ();
  ::libs::icore::xml::helpers::load_xml (&_helper_xml, _name, TypePath::appl_xml, _xml_doc);

  pugi::xml_node         _root  = _xml_doc.root ();
  base_functs::xml::ritn _nodes = _root.children ("property");

  if (_nodes.begin () == _nodes.end ())
    {
      XULOG_ERROR ("uuu_soft::BaseModule::load_appl_data::end1");
      return;
    }

  for (base_functs::xml::itn _it = _nodes.begin (); _it != _nodes.end (); ++_it)
    {
      if (event_props_.info_cpu_->check_node (_it))
        {
          event_props_.info_cpu_->load (_it);
          continue;
        }
      if (event_props_.main_appl_->check_node (_it))
        {
          event_props_.main_appl_->load (_it);
          continue;
        }
      if (event_props_.module_log_->check_node (_it))
        {
          event_props_.module_log_->load (_it);
          continue;
        }
      if (event_props_.storage_module_->check_node (_it))
        {
          event_props_.storage_module_->load (_it);
          continue;
        }
    }
  return;
}


void
BaseModule::update_events_props ()
{
  ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  ISharedProperty::guard_type _guard (_orinfo->get_sync ());

  if (_orinfo->get_main_appl_lockfree ())
    {
      return;
    }

  auto _main_appl = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::application::ApplicationProp> (event_props_.main_appl_);
  auto _info_cpu  = ::libs::iproperties::helpers::cast_event<InfoCPUEvent> (event_props_.info_cpu_);
  //auto = ::libs::iproperties::helpers::cast_event<>();

  _orinfo->set_main_appl_lockfree (_main_appl);

  if (::libs::helpers::sys::cpu::TypeExtCpu::max == _info_cpu->get_type ())
    {
      _info_cpu->set_type (cpu_informer_.get_max ());
    }

  if (0 == _info_cpu->get_count ())
    {
      _info_cpu->set_count (sys_info_->count_cpu ());
    }

  {
    const auto& _icpu = _orinfo->get_count_threads_lockfree ();

    _icpu->set_count_threads (_info_cpu->get_count ());
    _icpu->set_cpu (_info_cpu->get_type ());
  }

  _orinfo->set_appl_paths_lockfree (paths_);
  return;
}

}}}}      // namespace libs::ilink::appl::base
