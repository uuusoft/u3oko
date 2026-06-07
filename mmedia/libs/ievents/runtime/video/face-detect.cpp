/**
\file       face-detect.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "face-detect.hpp"

namespace libs::ievents::runtime::video
{
FaceDetect::FaceDetect (const Acessor& pha, bool start) :
  start_ (start)
{
  property_name_ = gen_get_mid ();
}


bool
FaceDetect::is_start () const
{
  return start_;
}


::libs::events::IEvent::ptr
FaceDetect::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (start_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::FaceDetect);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::video::FaceDetect);
