//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buffs-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace runtime { namespace mem {
/**
  \brief  Событие-уведомление с буферами под/c данными.
  */
class BuffsEvent : public RuntimeEvent
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
  // ext types
  using events_type = std::list<IEvent::ptr>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BuffsEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BuffsEvent);
  UUU_DISABLE_ACOPY_TYPE (BuffsEvent);

  explicit BuffsEvent (const Acessor& = Acessor (0));

  explicit BuffsEvent (const Acessor&, ::libs::buffs::Buffs::ptr& _buff, std::list<IEvent::ptr>* _events);

  virtual ~BuffsEvent ()
  {}

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/runtime/mem/buffs-event";
    return _ret;
  }

  ::libs::buffs::Buffs::ptr& get_buff ();

  void set_buff (::libs::buffs::Buffs::ptr&);

  events_type* get_events ();

  void set_events (events_type*);

  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  ::libs::buffs::Buffs::ptr buff_;        //< Буфер с данными, связанный с событием.
  events_type*              events_;      //< Список событий, связанный с буфером.

#if 0
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);
#endif

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::mem

//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::runtime::mem::BuffsEvent );
