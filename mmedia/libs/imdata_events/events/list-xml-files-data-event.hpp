#pragma once
/**
\file       list-xml-files-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
class DataGraphFolderInfoType final
{
  public:
  explicit DataGraphFolderInfoType (
    const std::string&                      name       = "",
    const ::libs::core::graph::GraphStates& path_state = ::libs::core::graph::GraphStates::unknown);

  virtual ~DataGraphFolderInfoType () = default;

  std::string                      folder_name_;   //<
  ::libs::core::graph::GraphStates graph_state_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

/// Событие содержит в себе список доступных xml файлов конфигурации графов обработки данных
/// Данный список может служить как список идентификаторов графов данных для событий ChangeGraphsDataEvent
class ListXmlFilesDataEvent : public BaseDataEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using data_graph_infos_types = std::list< DataGraphFolderInfoType >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ListXmlFilesDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ListXmlFilesDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ListXmlFilesDataEvent)

  explicit ListXmlFilesDataEvent (const Acessor& = Acessor (0), const data_graph_infos_types& = data_graph_infos_types ());
  virtual ~ListXmlFilesDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/imdata_events/events/list-xml-files-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_data_graph_states () const -> const data_graph_infos_types&;
  auto set_data_graph_states (data_graph_infos_types&& src) -> void;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseDataEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  data_graph_infos_types data_graph_states_;   //< Список состояний графов обработки данных
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::DataGraphFolderInfoType);
BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ListXmlFilesDataEvent);
