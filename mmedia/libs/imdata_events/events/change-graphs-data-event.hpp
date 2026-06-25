#pragma once
/**
\file       change-graphs-data-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
/// Событие производит указанное действие над указаным списком xml файлов для графов обработки данных
class ChangeGraphsDataEvent : public BaseDataEvent
{
  private:
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using id_folder_type         = std::string;
  using id_graphs_storage_type = std::list< id_folder_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangeGraphsDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangeGraphsDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ChangeGraphsDataEvent)

  explicit ChangeGraphsDataEvent (
    const Acessor&                        = Acessor (0),
    const GraphActions&           action  = GraphActions::get,
    const id_graphs_storage_type& folders = id_graphs_storage_type ());

  virtual ~ChangeGraphsDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/imdata_events/events/change-graphs-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_graph_folders () const -> const id_graphs_storage_type&;
  auto set_graph_folders (id_graphs_storage_type& folders) -> void;
  auto get_action () const -> GraphActions;
  auto set_action (const GraphActions& action) -> void;
  auto check () const -> bool;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseDataEvent)

  id_graphs_storage_type folders_;   //< Имя директории с XML файлами описания графа обработки данных и набором свойств для обновления параметров узлов графа, после создания
  GraphActions           action_;    //< Действие, которое требуется произвести со списком

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ChangeGraphsDataEvent);
