//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**     
\file       base-error-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "base-error-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace error {

BaseErrorEvent::BaseErrorEvent (const Acessor& _ph, const std::string& _info) :
  info_ (_info)
{
  property_name_ = gen_get_type_text_id ();
}


BaseErrorEvent::~BaseErrorEvent ()
{}


const std::string&
BaseErrorEvent::what () const
{
  return info_;
}


::libs::events::IEvent::ptr
BaseErrorEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<BaseErrorEvent> (this, _deep);
}


void
BaseErrorEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseErrorEvent);
  super::copy_int (_src);
  info_ = _dsrc->info_;
  return;
}


template <class Archive>
void
BaseErrorEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (info_);
  return;
}

}}}}      // namespace libs::ievents::runtime::error

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::error::BaseErrorEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::error::BaseErrorEvent);
