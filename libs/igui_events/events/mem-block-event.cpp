//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem-block-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "mem-block-event.hpp"
#include "mmedia/libs/helpers/proxy/mem-proxy-base.hpp"
#include "mmedia/modules/uuu_gui/io/includes.hpp"

namespace libs { namespace igui_events { namespace events {

MemBlockEvent::MemBlockEvent (const Acessor& _ph, const IBlockMem& _hmem, int _id) :
  hmem_ (_hmem),
  id_ (_id)
{
  property_name_ = gen_get_type_text_id ();
}


MemBlockEvent::~MemBlockEvent ()
{}


TypeEvents
MemBlockEvent::get_type () const
{
  return TypeEvents::mem_block;
}


IBlockMem
MemBlockEvent::get_hmem ()
{
  //UASSERT (hmem_.check ());
  return hmem_;
}


void
MemBlockEvent::set_hmem (const IBlockMem& _mem)
{
  hmem_ = _mem;
  return;
}


bool
MemBlockEvent::reset_video (void* _pmem) const
{
  UASSERT (_pmem);
  ::modules::uuu_gui::appl::io::VideoIO* _header = UUU_MEM_CAST<::modules::uuu_gui::appl::io::VideoIO*> (_pmem);
  _header->reset ();
  return true;
}


int
MemBlockEvent::get_id () const
{
  return id_;
}


::libs::events::IEvent::ptr
MemBlockEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<MemBlockEvent> (this, _deep);
}


void
MemBlockEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MemBlockEvent);
  super::copy_int (_src);
  hmem_ = _dsrc->hmem_;
  id_   = _dsrc->id_;
  return;
}


template <class Archive>
void
MemBlockEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  REF_UASSERT_SIGNAL ("failed");
  //ar & BOOST_SERIALIZATION_NVP( hmem_ );  Не реализовано.
  ar& BOOST_SERIALIZATION_NVP (id_);
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::MemBlockEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::MemBlockEvent);
