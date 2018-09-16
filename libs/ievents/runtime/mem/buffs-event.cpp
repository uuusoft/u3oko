//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buffs-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "buffs-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace mem {

BuffsEvent::BuffsEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
  events_        = nullptr;
}


BuffsEvent::BuffsEvent (const Acessor&, ::libs::buffs::Buffs::ptr& _buff, std::list<IEvent::ptr>* _events) :
  buff_ (_buff), events_ (_events)
{
  property_name_ = gen_get_mid ();
}


::libs::buffs::Buffs::ptr&
BuffsEvent::get_buff ()
{
  return buff_;
}


void
BuffsEvent::set_buff (::libs::buffs::Buffs::ptr& _buff)
{
  buff_ = _buff;
  return;
}


void
BuffsEvent::set_events (events_type* _events)
{
  events_ = _events;
  return;
}


BuffsEvent::events_type*
BuffsEvent::get_events ()
{
  return events_;
}


::libs::events::IEvent::ptr
BuffsEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BuffsEvent> (this, _deep);
}


void
BuffsEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BuffsEvent);
  super::copy_int (_src);
  //::libs::buffs::Buffs::ptr buff_;        //< Буфер с данными, связанный с событием.
  //events_type*              events_;      //< Список событий, связанный с буфером.
  UASSERT_SIGNAL ("unimplemented");
  return;
}

#if 0
  template<class Archive>
  void BuffsEvent::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( buff_ );
    return;
  }
#endif
}}}}      // namespace libs::ievents::runtime::mem

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::mem::BuffsEvent );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::runtime::mem::BuffsEvent );
