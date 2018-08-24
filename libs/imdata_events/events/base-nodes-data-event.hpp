//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       base-nodes-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
  \brief  Базовое события для событий работы с узлами пути обработки данных.
  */
class BaseNodesDataEvent : public BaseDataEvent
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
  typedef NodePathInfo                       node_type;
  typedef std::list<node_type>               nodes_list_type;
  typedef ChangePathsDataEvent::id_path_type id_path_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseNodesDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseNodesDataEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseNodesDataEvent);

  explicit BaseNodesDataEvent (const Acessor& = Acessor (0), const id_path_type& _id_path = id_path_type ());

  virtual ~BaseNodesDataEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/imdata_events/events/base-nodes-data-event";
    return _ret;
  }

  const id_path_type& get_id_path () const;

  void set_id_path (id_path_type&& _id);

  bool check () const;


  protected:
  virtual void load_int (const base_functs::xml::itn& _prop) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseDataEvent);

  id_path_type id_path_;      //< Идентификатор графа, с узлами которого требуется работать.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::BaseNodesDataEvent);
