/**
\file       video-buf-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "video-buf-event.hpp"

namespace libs::events_gui::events
{
VideoBufEvent::VideoBufEvent (const Acessor& pha, Bufs::ptr buf, int id) :
  buf_ (std::move (buf)),
  id_ (id)
{
}


VideoBufEvent::~VideoBufEvent () = default;


auto
VideoBufEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoBufEvent::gen_get_mid ();
}


auto
VideoBufEvent::get_type () const -> TypeEvents
{
  return TypeEvents::video_buf;
}

auto
VideoBufEvent::get_buf () const -> const Bufs::ptr
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


auto
VideoBufEvent::get_id () const -> int
{
  return id_;
}


auto
VideoBufEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
  // ar & BOOST_SERIALIZATION_NVP( hmem_ );
  arh& BOOST_SERIALIZATION_NVP (id_);
  U3_THROW_EXCEPT ("try serializate VideoBufEvent");
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::VideoBufEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::VideoBufEvent);
