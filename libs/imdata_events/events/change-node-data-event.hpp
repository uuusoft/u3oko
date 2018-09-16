//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       change-node-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Событие производит указанное действие над указаним списком xml файлов для графов обработки данных.
*/
class ChangeNodeDataEvent : public BaseNodesDataEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  using id_path_type      = std::string;
  using id_node_path_type = ::libs::core::path::PathObjID;
  using events_list_type  = std::list<IEvent::ptr>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangeNodeDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangeNodeDataEvent);
  UUU_DISABLE_ACOPY_TYPE (ChangeNodeDataEvent);
  /**
  \brief          Рабочий конструктор.
  \param[in]      _action   действие, которое надо произвести над событиями узла графа.
  \param[in]      _id_path  идентфикатор графа.
  \param[in]      _id_node  идентфикатор узла в графе.
  \param[in, out] _events   события.
  */
  explicit ChangeNodeDataEvent (
    const Acessor&                       = Acessor (0),
    const ChangeNodePathAction& _action  = ChangeNodePathAction::get,
    const id_path_type&         _id_path = "",
    const id_node_path_type&    _id_node = id_node_path_type (),
    const events_list_type&     _events  = events_list_type ());

  virtual ~ChangeNodeDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/imdata_events/events/change-node-data-event";
    return _ret;
  }

  const id_node_path_type& get_node () const;

  void set_node (const id_node_path_type& _path);

  ChangeNodePathAction get_action () const;

  void set_action (const ChangeNodePathAction& _action);

  const events_list_type& get_events () const;

  void set_events (const events_list_type& _action);

  bool check () const;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseNodesDataEvent);

  id_node_path_type    id_node_;      //< Идентификатор узла графа.
  ChangeNodePathAction action_;       //< Действие, которое требуется произвести со списком событий узлу. Установить/Получить/etc.
  events_list_type     events_;       //< События-свойства узла графа. Используется список например для быстрого получения всех свойств указанного узла.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual void                        load_int (const base_functs::xml::itn& _prop) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ChangeNodeDataEvent);
