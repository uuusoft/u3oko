#pragma once
/**
\file       base-gui-event.hpp  
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
/**
  \brief  Базовый класс всех событий подсистемы GUI.
  */
class BaseGUIEvent : public ::libs::ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseGUIEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseGUIEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseGUIEvent);

  BaseGUIEvent (const Acessor& = Acessor (0));

  virtual ~BaseGUIEvent ();

  virtual TypeEvents get_type () const;

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/igui_events/events/props/base-gui-event";
    return _ret;
  }


  protected:
  virtual bool check_node_int (const base_functs::xml::itn& /*_node*/) override;
  virtual void load_int (const base_functs::xml::itn& _node) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::BaseGUIEvent);
