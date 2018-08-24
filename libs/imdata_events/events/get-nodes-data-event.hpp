//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get-nodes-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
  \brief  Событие возвращает список узлов указанного графа обработки данных.
  */
class GetNodesDataEvent : public BaseNodesDataEvent
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
  typedef NodePathInfo         node_type;
  typedef std::list<node_type> nodes_list_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (GetNodesDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetNodesDataEvent);
  UUU_DISABLE_ACOPY_TYPE (GetNodesDataEvent);

  explicit GetNodesDataEvent (
    const Acessor&                  = Acessor (0),
    const id_path_type&    _id_path = "",
    const nodes_list_type& _nodes   = nodes_list_type ());

  virtual ~GetNodesDataEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/imdata_events/events/get-nodes-data-event";
    return _ret;
  }

  const nodes_list_type& get_nodes () const;

  void set_nodes (nodes_list_type& _nodes);

  bool check () const;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseNodesDataEvent);

  nodes_list_type nodes_;      //< Списк узлов в графе обработки данных.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual void                        load_int (const base_functs::xml::itn& _prop) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::GetNodesDataEvent);
