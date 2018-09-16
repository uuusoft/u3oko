#pragma once
/**
\file       command-code-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
/**
\brief  Тип для командного сообщения интерфейса.
*/
class CommandCodeEvent : public BaseGUIEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (CommandCodeEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (CommandCodeEvent);
  UUU_DISABLE_ACOPY_TYPE (CommandCodeEvent);

  explicit CommandCodeEvent (const Acessor& = Acessor (0), const std::string& _code = "null");

  virtual ~CommandCodeEvent ();

  virtual TypeEvents get_type () const override;

  std::string get_code () const;

  void set_code (const std::string&);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/igui_events/events/props/CommandCodeEvent";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseGUIEvent);

  std::string code_;      //< ???

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::CommandCodeEvent);
