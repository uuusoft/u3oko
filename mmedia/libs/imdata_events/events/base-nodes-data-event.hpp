#pragma once
/**
\file       base-nodes-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
/// Базовое события для событий работы с узлами пути обработки данных
class BaseNodesDataEvent : public BaseDataEvent
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
  using node_type       = NodeGraphInfo;
  using nodes_list_type = std::list< node_type >;
  using id_graph_type   = ChangeGraphsDataEvent::id_folder_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseNodesDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseNodesDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseNodesDataEvent)

  explicit BaseNodesDataEvent (const Acessor& = Acessor (0), const id_graph_type& id_graph = id_graph_type ());
  virtual ~BaseNodesDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/imdata_events/events/base-nodes-data-event";
    return ret;
  }

  const id_graph_type& get_id_graph () const;
  void                 set_id_graph (id_graph_type&& id);
  bool                 check () const;

  protected:
  // virtual void load_int (const ::pugi::xml_named_node_iterator& prop) override;
  virtual void load_json_int (const ::boost::json::object& obj) override;
  virtual void save_json_int (::boost::json::object& obj) const override;
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseDataEvent)

  id_graph_type id_graph_;   //< Идентификатор графа, с узлами которого требуется работать

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::BaseNodesDataEvent);
