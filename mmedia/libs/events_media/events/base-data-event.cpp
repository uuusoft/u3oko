/**
\file       base-data-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_media
\brief      Реализация базового класса события модуля обработки данных
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-data-event.hpp"

namespace libs::events_media::events
{
BaseDataEvent::BaseDataEvent (const Acessor& pha)
{
}


auto
BaseDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseDataEvent::gen_get_mid ();
}


auto
BaseDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseDataEvent > (this, deep);
}


void
BaseDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
}


void
BaseDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
}


void
BaseDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseDataEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::BaseDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::BaseDataEvent);
