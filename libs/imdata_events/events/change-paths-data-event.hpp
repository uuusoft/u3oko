#pragma once
/**
\file       change-paths-data-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief    
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Событие производит указанное действие над указаним списком xml файлов для графов обработки данных.
*/
class ChangePathsDataEvent : public BaseDataEvent
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
  using id_path_type       = std::string;
  using id_paths_list_type = std::list<id_path_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangePathsDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangePathsDataEvent);
  UUU_DISABLE_ACOPY_TYPE (ChangePathsDataEvent);

  explicit ChangePathsDataEvent (
    const Acessor&                    = Acessor (0),
    const ChangePathAction&   _action = ChangePathAction::get,
    const id_paths_list_type& _paths  = id_paths_list_type ());

  virtual ~ChangePathsDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/imdata_events/events/change-paths-data-event";
    return _ret;
  }

  const id_paths_list_type& get_paths () const;

  void set_paths (id_paths_list_type& _paths);

  ChangePathAction get_action () const;

  void set_action (const ChangePathAction& _action);

  bool check () const;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseDataEvent);

  id_paths_list_type paths_;       //< Имя XML файла с описанием графа обработки данных.
  ChangePathAction   action_;      //< Действие, которое требуется произвести со списком.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual void                        load_int (const base_functs::xml::itn& _prop) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ChangePathsDataEvent);
