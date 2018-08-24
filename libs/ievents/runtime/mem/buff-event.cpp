//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "buff-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace mem {

BuffEvent::BuffEvent (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


BuffEvent::BuffEvent (IVideoBuff::cptr& _buff)
{
  if (_buff)
    {
      buff_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ()->get ();
      buff_->clone (&*_buff, 100.0f);
    }

  property_name_ = gen_get_type_text_id ();
  return;
}


IVideoBuff::ptr&
BuffEvent::get_buff ()
{
  return buff_;
}


::libs::events::IEvent::ptr
BuffEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<BuffEvent> (this, _deep);
}


void
BuffEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BuffEvent);
  super::copy_int (_src);
  //buff_
  UASSERT_SIGNAL ("unimplemented");
  return;
}

#if 0
  template<class Archive>
  void BuffEvent::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( buff_ );
    return;
  }
  template void BuffEvent::s1erialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned int );
  template void BuffEvent::s1erialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned int );
#endif
}}}}      // namespace libs::ievents::runtime::mem

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::mem::BuffEvent );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::runtime::mem::BuffEvent );
