/**
\file       base-error-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "base-error-event.hpp"

namespace libs::events_base::runtime::error
{
BaseErrorEvent::BaseErrorEvent (const Acessor& pha, std::string info) :
  info_ (std::move (info))
{
}


auto
BaseErrorEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseErrorEvent::gen_get_mid ();
}


auto
BaseErrorEvent::what () const -> const std::string&
{
  return info_;
}


auto
BaseErrorEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseErrorEvent > (this, deep);
}


void
BaseErrorEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseErrorEvent > (src);
  super::copy_int (src);
  info_ = dsrc->info_;
}


template< class Archive >
void
BaseErrorEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (info_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::error

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::error::BaseErrorEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::error::BaseErrorEvent);
