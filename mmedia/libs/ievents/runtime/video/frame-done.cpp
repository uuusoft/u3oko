/**
\file       frame-done.cpp
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "frame-done.hpp"

namespace libs::ievents::runtime::video
{
FrameDone::FrameDone (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


FrameDone::~FrameDone ()
{
}


::libs::events::IEvent::ptr
FrameDone::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< FrameDone > (this, deep);
}


void
FrameDone::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (FrameDone);
  super::copy_int (src);
}


template< class Archive >
void
FrameDone::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);

  self_correct ();
}
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::FrameDone);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::video::FrameDone);
