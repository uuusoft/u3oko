/**
\file       base-data-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_imdata_events
\brief      Реализация базового класса события модуля обработки данных
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-data-event.hpp"

namespace libs::imdata_events::events
{
BaseDataEvent::BaseDataEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BaseDataEvent::~BaseDataEvent ()
{
}


::libs::events::IEvent::ptr
BaseDataEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  U3_CHECK_COPY_EVENT (BaseDataEvent);
  super::copy_int (src);
}


template< class Archive >
void
BaseDataEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::BaseDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::BaseDataEvent);
