#pragma once
/**
\file       data-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_data
\brief      Модуль захвата и обработки данных
*/

namespace modules::uuu_mdata::appl::helpers
{
std::string make_file_name_for_save_event (const syn::NodeID::name_id_type& id_node, const std::string& id_event);
void        split_event_file_name2parts (const std::string& file_name, syn::NodeID::name_id_type& id_node, std::string& id_event);
}   // namespace modules::uuu_mdata::appl::helpers


namespace modules::uuu_mdata::appl
{
/// Реализация "приложения" для модуля захвата и обработки данных
class DataModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  DataModule ();
  virtual ~DataModule () = default;

  private:
  //  internal typess
  using ptr_graph_type = ::libs::core::graph::IGraph::weak_ptr;
  using id_graph_type  = std::string;
  using graphs_type    = std::unordered_map< id_graph_type, ptr_graph_type >;
  using lock_type      = ::libs::properties::ISharedProperty::lock_type;

  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  //  IApplication overrides
  virtual void init_appl_data_int () override;

  //  BaseModule overrides
  virtual void appl_init_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_done_int () override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_proxys_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (syn::IEvent::ptr& evnt) override;
  virtual bool            is_now_thread_to_sleep (bool now_recv_evnt) override;

  void           catch_cmd_msgs (syn::CommandCodeEvent::raw_ptr msg);
  void           catch_data_msgs (syn::IEvent::ptr& msg);
  bool           check_process ();
  ptr_graph_type get_graph (const id_graph_type& id);

  void send_msg2graph (
    const id_graph_type&             id,
    const syn::NodeID::name_id_type& id_req_obj,
    syn::IEvent::ptr&                msg);

  // U3-REFACT
  void               update_cpu_graph (const id_graph_type& id);
  void               update_events_graph (const id_graph_type& id);
  std::string        find_template_for_graph (const std::string& folder) const;
  void               update_template_for_graph (const std::string& path2folder, const std::string& folder) const;
  bool               is_graph_folder_exist (const std::string& folder) const;
  void               prepare_graph (const std::string& folder);
  void               make_data_graph (const std::string& name_xml);
  void               start_graph (const id_graph_type& id);
  void               stop_graph (const id_graph_type& id);
  void               delete_graph (const id_graph_type& id, bool permanent = false);
  void               process_info_cpu (syn::InfoCPUEvent::raw_ptr);
  void               process_change_graphs_data (syn::ChangeGraphsDataEvent::raw_ptr);
  void               process_list_xml_files (syn::ListXmlFilesDataEvent::raw_ptr);
  syn::NodeEnumFiles get_list_xml_files ();
  void               process_list_devices (syn::ListDevicesDataEvent::raw_ptr, syn::IEvent::ptr& msg);
  void               process_get_nodes (syn::GetNodesDataEvent::raw_ptr);
  void               process_change_node (syn::ChangeNodeDataEvent::raw_ptr, syn::IEvent::ptr&);
  void               process_expand_times (syn::ExpandTimesEvent::raw_ptr, syn::IEvent::ptr&);
  syn::GraphStates   get_data_graph_state (const std::string& folder) const;
  void               set_data_graph_state (const std::string& folder, const ::libs::core::graph::GraphStates& state);

  ::libs::core::ICore::ptr icore_;             //< Текущая выбранная реализация ядра модуля обработки данных
  syn::Loader::ptr         resource_loader_;   //< Загрузчик статических ресурсов (файлов, скриптов etc) в память, требуется для унифицированной поддержки ОС
  graphs_type              idatas_;            //< Активные графы обработки данных
  syn::IEvent::ptr         devices_;           //< список доступных источников
};
}   // namespace modules::uuu_mdata::appl
