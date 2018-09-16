#pragma once
/**
\file       mouse-button-down-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
/**
\brief  empty brief
*/
class MouseButtonDownEvent : public BaseGUIEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MouseButtonDownEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MouseButtonDownEvent);
  UUU_DISABLE_ACOPY_TYPE (MouseButtonDownEvent);

  explicit MouseButtonDownEvent (
    const Acessor&                = Acessor (0),
    const TypeMouseButton&  _type = TypeMouseButton (),
    const utils::IPos::ptr& _pos  = utils::IPos::ptr ());

  virtual ~MouseButtonDownEvent ();

  virtual TypeEvents get_type () const override;

  TypeMouseButton get_type_button () const;

  void set_type_button (const TypeMouseButton&);

  utils::IPos::ptr get_pos () const;

  void set_pos (const utils::IPos::ptr&);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/igui_events/events/props/mouse-button-down-event";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseGUIEvent);

  TypeMouseButton  type_;      //< ???
  utils::IPos::ptr pos_;       //< ???

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::MouseButtonDownEvent);
