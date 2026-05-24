/**
\file       base-error-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "base-error-event.hpp"

namespace libs::ievents::runtime::error
{
BaseErrorEvent::BaseErrorEvent (const Acessor& ph, const std::string& info) :
  info_ (info)
{
  property_name_ = gen_get_mid ();
}


BaseErrorEvent::~BaseErrorEvent ()
{
}


const std::string&
BaseErrorEvent::what () const
{
  return info_;
}


::libs::events::IEvent::ptr
BaseErrorEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseErrorEvent > (this, deep);
}


void
BaseErrorEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BaseErrorEvent);
  super::copy_int (src);
  info_ = dsrc->info_;
}


template< class Archive >
void
BaseErrorEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  ar& BOOST_SERIALIZATION_NVP (info_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::error

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::error::BaseErrorEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::error::BaseErrorEvent);
