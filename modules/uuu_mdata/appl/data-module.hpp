#pragma once
/**
\file       data-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      Модуль захвата и обработки данных.
*/

namespace modules { namespace uuu_mdata { namespace appl {
/**
  \brief  Реализация "приложения" для модуля захвата и обработки данных.
  */
class DataModule : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  DataModule ();

  virtual ~DataModule ();


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule);

  using ptr_path_type = ::libs::core::path::IPath::weak_ptr;
  using id_path_type  = std::string;
  using paths_type    = std::map<id_path_type, ptr_path_type>;

  //  ::libs::link::appl::IApplication override
  virtual void init_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void init_proxys_int () override;
  virtual bool deinit_int () override;
  virtual void update_catch_functs_int () override;

  //  LeafModule override
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (IEvent::ptr _evnt) override;
  virtual bool            is_now_sleep_thread (bool _now_recv_evnt) override;

  void catch_cmd_msgs (::libs::igui_events::events::CommandCodeEvent::raw_ptr _msg);

  void catch_data_msgs (::libs::events::IEvent::ptr& _msg);

  bool check_process ();

  ptr_path_type get_path (const id_path_type& _id);

  void send_msg2path (const id_path_type& _id, ::libs::events::IEvent::ptr _msg);

  void update_cpu_path (const id_path_type& _id);

  void make_path (const std::string& _name_xml);

  void start_path (const id_path_type& _id);

  void stop_path (const id_path_type& _id);

  void delete_path (const id_path_type& _id);

  void process_info_cpu(InfoCPUEvent::raw_ptr);

  void process_change_paths_data(ChangePathsDataEvent::raw_ptr);

  void process_list_xml_files ( ListXmlFilesDataEvent::raw_ptr );

  void process_get_nodes(GetNodesDataEvent::raw_ptr);

  void process_change_node(ChangeNodeDataEvent::raw_ptr, IEvent::ptr&);

  void process_expand_time_statistic(ExpandTimeStatisticEvent::raw_ptr, IEvent::ptr&);

  ::libs::core::ICore::ptr icore_;       //< Текущая выбранная реализация ядра модуля обработки данных.
  paths_type               idatas_;      //< Активные графы обработки данных.
};

}}}      // namespace modules::uuu_mdata::appl
