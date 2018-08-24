#pragma once
/**
\file       video-buff-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
//  syn
typedef ::libs::buffs::Buffs Buffs;
/**
  \brief  empty brief
  */
class VideoBuffEvent : public BaseGUIEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoBuffEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoBuffEvent);
  UUU_DISABLE_ACOPY_TYPE (VideoBuffEvent);

  explicit VideoBuffEvent (const Acessor& = Acessor (0), const Buffs::ptr& _buff = ::libs::buffs::Buffs::ptr (), int _id = 0);

  virtual ~VideoBuffEvent ();

  virtual TypeEvents get_type () const override;

  const Buffs::ptr get_buff () const;

  void set_buff (Buffs::ptr&);

  int get_id () const;

  void set_id (int);

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/igui_events/events/props/video-buff-event";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseGUIEvent);

  Buffs::ptr buff_;      //< ???
  int        id_;        //< ???

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::VideoBuffEvent);
