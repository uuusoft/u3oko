/**
\file       mem-block-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    uuu_igui_evenets
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "mem-block-event.hpp"
#include "mmedia/libs/helpers/proxy/mem-proxy-base.hpp"
#include "mmedia/modules/uuu_gui/io/includes.hpp"

namespace libs::igui_events::events
{
MemBlockEvent::MemBlockEvent (const Acessor& ph, const ::libs::link::mem::IBlockFakeMem& hmem, int id) :
  hmem_ (hmem),
  id_ (id)
{
  property_name_ = gen_get_mid ();
}


MemBlockEvent::~MemBlockEvent ()
{
}


TypeEvents
MemBlockEvent::get_type () const
{
  return TypeEvents::mem_block;
}


::libs::link::mem::IBlockFakeMem
MemBlockEvent::get_hmem ()
{
  return hmem_;
}


void
MemBlockEvent::set_hmem (const ::libs::link::mem::IBlockFakeMem& mem)
{
  hmem_ = mem;
  return;
}


bool
MemBlockEvent::reset_video (void* pmem) const
{
  U3_ASSERT (pmem);
  ::modules::uuu_gui::appl::io::VideoIO* header = U3_CAST_REINTERPRET< ::modules::uuu_gui::appl::io::VideoIO* > (pmem);
  header->reset ();
  return true;
}


int
MemBlockEvent::get_id () const
{
  return id_;
}


::libs::events::IEvent::ptr
MemBlockEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MemBlockEvent > (this, deep);
}


void
MemBlockEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (MemBlockEvent);
  super::copy_int (src);
  hmem_ = dsrc->hmem_;
  id_   = dsrc->id_;
}


template< class Archive >
void
MemBlockEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
  U3_ASSERT_SIGNAL ("failed");
  // ar & BOOST_SERIALIZATION_NVP( hmem_ );  Не реализовано.
  ar& BOOST_SERIALIZATION_NVP (id_);

  self_correct ();
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::MemBlockEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::MemBlockEvent);
