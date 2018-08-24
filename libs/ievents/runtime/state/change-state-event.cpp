//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       change-state-event.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "change-state-event.hpp"


namespace libs { namespace ievents { namespace runtime { namespace state {

ChangStateProcessTypeEvent::ChangStateProcessTypeEvent (const Acessor& _ph, bool _start) :
  start_ (_start)
{
  property_name_ = gen_get_type_text_id ();
}


ChangStateProcessTypeEvent::~ChangStateProcessTypeEvent ()
{}


bool
ChangStateProcessTypeEvent::is_start () const
{
  return start_;
}


void
ChangStateProcessTypeEvent::set_start (bool _val)
{
  start_ = _val;
  return;
}


::libs::events::IEvent::ptr
ChangStateProcessTypeEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ChangStateProcessTypeEvent> (this, _deep);
}


void
ChangStateProcessTypeEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ChangStateProcessTypeEvent);
  super::copy_int (_src);
  start_ = _dsrc->start_;
  return;
}


template <class Archive>
void
ChangStateProcessTypeEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (start_);
  return;
}

}}}}      // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::state::ChangStateProcessTypeEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::state::ChangStateProcessTypeEvent);
