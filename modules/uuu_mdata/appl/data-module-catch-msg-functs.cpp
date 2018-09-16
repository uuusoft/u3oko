//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       data-module-catch-msg-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "data-module.hpp"

namespace modules { namespace uuu_mdata { namespace appl {

void
DataModule::process_info_cpu (InfoCPUEvent::raw_ptr _props)
{
  event_props_.info_cpu_->copy (_props);

  std::for_each (idatas_.begin (), idatas_.end (), [this](paths_type::value_type& _val) {
    update_cpu_path (_val.first);
    return;
  });
  return;
}


void
DataModule::process_change_paths_data (ChangePathsDataEvent::raw_ptr _props)
{
  const auto& _action = _props->get_action ();

  switch (_action)
    {
    case ::libs::imdata_events::events::ChangePathAction::get:
      {
        ChangePathsDataEvent::id_paths_list_type _paths;
        for (const auto& _val : idatas_)
          {
            _paths.push_back (_val.first);
          }
        _props->set_paths (_paths);
        break;
      }
    case ::libs::imdata_events::events::ChangePathAction::add:
      {
        for (const auto& _path : _props->get_paths ())
          {
            make_path (_path);
            update_cpu_path (_path);
            start_path (_path);
          }
        break;
      }
    case ::libs::imdata_events::events::ChangePathAction::remove:
      {
        for (const auto& _path : _props->get_paths ())
          {
            delete_path (_path);
          }
        break;
      }
    default:
      XULOG_ERROR ("unknown type ChangePathAction " << to_str (UUU_ICAST_INT (_action)));
      break;
    }
  return;
}


void
DataModule::process_list_xml_files (ListXmlFilesDataEvent::raw_ptr _props)
{
  auto _apppaths = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();

  ::libs::icore::xml::TInitInfo     _loader_info (_apppaths);
  ::libs::icore::xml::Loader        _loader (_loader_info);
  ::libs::icore::xml::NodeEnumFiles _files;

  _loader.get_enum (::libs::icore::xml::TypePath::data_xml, _files);

  ListXmlFilesDataEvent::xml_files_type _files2event (_files.files_.begin (), _files.files_.end ());
  _props->set_xml_files (std::move (_files2event));
  return;
}


void
DataModule::process_get_nodes (GetNodesDataEvent::raw_ptr _props)
{
  const auto& _id_path = _props->get_id_path ();
  auto        _find_it = idatas_.find (_id_path);

  if (_find_it == idatas_.end ())
    {
      return;
    }
  if (auto _find_path = _find_it->second.lock ())
    {
      const auto                         _objs = _find_path->get_objs ();
      GetNodesDataEvent::nodes_list_type _nodes;

      for (const auto& _obj : _objs)
        {
          _nodes.push_back (GetNodesDataEvent::node_type (_obj.get_name (), _obj.get_name_dll ()));
        }
      _props->set_nodes (_nodes);
    }
  return;
}


void
DataModule::process_change_node (ChangeNodeDataEvent::raw_ptr _props, IEvent::ptr& _msg)
{
  const auto& _id_path = _props->get_id_path ();
  auto        _find_it = idatas_.find (_id_path);

  if (_find_it == idatas_.end ())
    {
      DATA_LOG (("path not found by id, " + _id_path).c_str ());
      //UASSERT_SIGNAL( "path not found by id" );
      return;
    }

  auto _find_path = _find_it->second.lock ();
  if (!_find_path)
    {
      DATA_LOG (("try use empty path id, " + _id_path).c_str ());
      UASSERT_SIGNAL ("try use empty path id");
      return;
    }

  auto _objs   = _find_path->get_objs ();
  auto _id_obj = _props->get_node ();
  _find_path->send_event2obj (_id_obj, _msg);
  return;
}


void
DataModule::process_expand_time_statistic (ExpandTimeStatisticEvent::raw_ptr _props, IEvent::ptr& _msg)
{
  switch (_props->get_source ())
    {
    case revents::state::TypeStatisticSource::alg:
    case revents::state::TypeStatisticSource::path_obj:
      {
        const std::string _id_path = "???";                 // _props->get_id_path();
        auto              _find_it = idatas_.begin ();      // find( _id_path );

        if (_find_it == idatas_.end ())
          {
            XULOG_WARNING ("path not found, " << _id_path);
            DATA_LOG ("path not found, " + _id_path);
            return;
          }

        auto _find_path = _find_it->second.lock ();
        if (!_find_path)
          {
            XULOG_WARNING ("try use empty path, " << _id_path);
            DATA_LOG ("try use empty path, " + _id_path);
            return;
          }

        _find_path->send_event2obj (::libs::core::path::PathObjID (), _msg);
        break;
      }
    default:
      XULOG_WARNING ("unknown type TypeStatisticSource");
      break;
    }
  return;
}

}}}      // namespace modules::uuu_mdata::appl
