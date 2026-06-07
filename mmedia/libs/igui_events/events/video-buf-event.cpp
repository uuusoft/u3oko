/**
\file       video-buf-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "video-buf-event.hpp"

namespace libs::igui_events::events
{
VideoBufEvent::VideoBufEvent (const Acessor& pha, const Bufs::ptr& buf, int id) :
  buf_ (buf),
  id_ (id)
{
  property_name_ = gen_get_mid ();
}


VideoBufEvent::~VideoBufEvent ()
{
}


TypeEvents
VideoBufEvent::get_type () const
{
  return TypeEvents::video_buf;
}

const Bufs::ptr
VideoBufEvent::get_buf () const
{
  U3_ASSERT (buf_);
  return buf_;
}


void
VideoBufEvent::set_buf (Bufs::ptr& buf)
{
  buf_ = buf;
  return;
}


void
VideoBufEvent::set_id (int id)
{
  id_ = id;
  return;
}


int
VideoBufEvent::get_id () const
{
  return id_;
}


::libs::events::IEvent::ptr
VideoBufEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoBufEvent > (this, deep);
}


void
VideoBufEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoBufEvent > (src);
  super::copy_int (src);

  buf_ = dsrc->buf_;
  id_  = dsrc->id_;
}


template< class Archive >
void
VideoBufEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
  // ar & BOOST_SERIALIZATION_NVP( hmem_ );
  arh& BOOST_SERIALIZATION_NVP (id_);
  U3_THROW_EXCEPTION ("try serializate VideoBufEvent");
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::VideoBufEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::VideoBufEvent);
