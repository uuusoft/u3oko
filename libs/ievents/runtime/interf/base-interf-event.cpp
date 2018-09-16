//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       interf-correct-image-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "base-interf-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace interf {

BaseInterfEvent::BaseInterfEvent (const Acessor& _ph) :
  active_ (false)
{
  property_name_ = gen_get_mid ();
}


BaseInterfEvent::~BaseInterfEvent ()
{}


void
BaseInterfEvent::set_active (bool _active)
{
  active_ = _active;
  return;
}


bool
BaseInterfEvent::is_active () const
{
  return active_;
}


void
BaseInterfEvent::set_available (bool _enable)
{
  available_ = _enable;
  return;
}


bool BaseInterfEvent::is_available () const
{
  return available_;
}


::libs::events::IEvent::ptr
BaseInterfEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseInterfEvent> (this, _deep);
}

void
BaseInterfEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseInterfEvent);
  super::copy_int (_src);
  active_    = _dsrc->active_;
  available_ = _dsrc->available_;
  return;
}

#if 0
  template<class Archive>
  void BaseInterfEvent::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( impl_ );
    ar & active_;
    return;
  }
#endif
}}}}      // namespace libs::ievents::runtime::interf

#if 0
BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::interf::BaseInterfEvent );
SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::runtime::interf::BaseInterfEvent );
#endif
