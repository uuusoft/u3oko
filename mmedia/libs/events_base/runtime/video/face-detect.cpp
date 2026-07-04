/**
\file       face-detect.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "face-detect.hpp"

namespace libs::events_base::runtime::video
{
FaceDetect::FaceDetect (const Acessor& pha, bool start) :
  start_ (start)
{
}


auto
FaceDetect::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return FaceDetect::gen_get_mid ();
}


auto
FaceDetect::is_start () const -> bool
{
  return start_;
}


auto
FaceDetect::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< FaceDetect > (this, deep);
}


void
FaceDetect::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< FaceDetect > (src);
  super::copy_int (src);
  start_ = dsrc->start_;
}


template< class Archive >
void
FaceDetect::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (start_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::video::FaceDetect);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::video::FaceDetect);
