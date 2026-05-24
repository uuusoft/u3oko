#pragma once
/**
\file       change-graphs-data-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  virtual ~ChangeGraphsDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/imdata_events/events/change-graphs-data-event";
    return ret;
  }

  const id_graphs_storage_type& get_graph_folders () const;
  void                          set_graph_folders (id_graphs_storage_type& folders);
  GraphActions                  get_action () const;
  void                          set_action (const GraphActions& action);
  bool                          check () const;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseDataEvent)

  id_graphs_storage_type folders_;   //< Имя директории с XML файлами описания графа обработки данных и набором свойств для обновления параметров узлов графа, после создания
  GraphActions           action_;    //< Действие, которое требуется произвести со списком

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ChangeGraphsDataEvent);
