/**
\file       mem-block-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "mem-block-event.hpp"
#include "mmedia/libs/utility/proxy/mem-proxy-base.hpp"
#include "mmedia/modules/mgui/io/includes.hpp"

namespace libs::events_gui::events
{
MemBlockEvent::MemBlockEvent (const Acessor& pha, const ::libs::link::mem::IBlockFakeMem& hmem, int id) :
  hmem_ (hmem),
  id_ (id)
{
}


MemBlockEvent::~MemBlockEvent () = default;


auto
MemBlockEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return MemBlockEvent::gen_get_mid ();
}


auto
MemBlockEvent::get_type () const -> TypeEvents
{
  return TypeEvents::mem_block;
}


auto
MemBlockEvent::get_hmem () -> ::libs::link::mem::IBlockFakeMem
{
  return hmem_;
}


void
MemBlockEvent::set_hmem (const ::libs::link::mem::IBlockFakeMem& mem)
{
  hmem_ = mem;
  return;
}


auto
MemBlockEvent::reset_video (void* pmem) const -> bool
{
  U3_ASSERT (pmem);
  auto* header = ::libs::utility::casts::reinterpret_cast_helper< ::modules::mgui::appl::io::VideoIO* > (pmem);
  header->reset ();
  return true;
}


auto
MemBlockEvent::get_id () const -> int
{
  return id_;
}


auto
MemBlockEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< MemBlockEvent > (this, deep);
}


void
MemBlockEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MemBlockEvent > (src);
  super::copy_int (src);
  hmem_ = dsrc->hmem_;
  id_   = dsrc->id_;
}


template< class Archive >
void
MemBlockEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
  U3_ASSERT_SIGNAL ("failed");
  // ar & BOOST_SERIALIZATION_NVP( hmem_ );  Не реализовано.
  arh& BOOST_SERIALIZATION_NVP (id_);

  self_correct ();
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::MemBlockEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::MemBlockEvent);
