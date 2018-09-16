//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       leaf-module-event-props-functs.cpp
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
#include "leaf-module.hpp"
// old shit
namespace libs { namespace ilink { namespace appl { namespace leaf {

#if 0
  void LeafModule::load_events_props()
  {
    super::();
    const std::string             _name ("appl.xml");
    pugi::xml_document            _xml_doc;
    ::libs::icore::xml::TInitInfo _helper_info( std::const_pointer_cast<const ::libs::iproperties::appl_paths::IAppPaths>(paths_) );
    ::libs::icore::xml::Loader    _helper_xml( _helper_info );
    
    event_props_.init();

    ::libs::icore::xml::helpers::load_xml( &_helper_xml, _name, TypePath::appl_xml, _xml_doc );
    //_helper_xml.load( _name, TypePath::appl_xml, _xml_doc );

    pugi::xml_node      _root = _xml_doc.root ();
    base_functs::xml::ritn  _nodes  = _root.children ("property");

    if ( _nodes.begin () == _nodes.end () )
    {
      XULOG_ERROR( "uuu_soft::LeafModule::load_appl_data::end1");
      return;
    }

    for ( base_functs::xml::itn _it = _nodes.begin (); _it != _nodes.end (); ++_it )
    {
      if ( event_props_.info_cpu_->check_node ( _it ) )
      {
        event_props_.info_cpu_->load ( _it );
        continue;
      }

      if ( event_props_.main_appl_->check_node ( _it ) )
      {
        event_props_.main_appl_->load ( _it );
        continue;
      }

      if ( event_props_.module_log_->check_node ( _it ) )
      {
        event_props_.module_log_->load ( _it );
        continue;
      }
    }

    return;
  }


  void LeafModule::update_events_props()
  {
    super::();

    ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST(ISystemProperty::raw_ptr)(::libs::iproperties::helpers::get_shared_prop_os ());
    ISharedProperty::guard_type _guard (_orinfo->get_sync ());

    if ( _orinfo->get_main_appl_lockfree () )
    {
      return;
    }
    
    _orinfo->set_main_appl_lockfree ( event_props_.main_appl_ );

    if ( ::libs::helpers::sys::cpu::TypeExtCpu::max == event_props_.info_cpu_->get_type () )
    {
      event_props_.info_cpu_->set_type ( cpu_informer_.get_max () );
    }

    if ( 0 == event_props_.info_cpu_->get_count () )
    {
      event_props_.info_cpu_->set_count (sys_info_->count_cpu ());
    }

    _orinfo->get_count_threads_lockfree ()->set_count_threads ( event_props_.info_cpu_->get_count () );
    _orinfo->get_count_threads_lockfree ()->set_cpu ( event_props_.info_cpu_->get_type () );
    _orinfo->set_appl_paths_lockfree ( paths_ );
    return;
  }
#endif

}}}}      // namespace libs::ilink::appl::leaf
