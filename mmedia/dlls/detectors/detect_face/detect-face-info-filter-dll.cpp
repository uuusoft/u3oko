/**
\file       detect-face-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_detect_face
*/
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"

namespace dlls::detectors::detect_face
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoDetectProp > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
  detector_ = dlib::get_frontal_face_detector ();
}
}   // namespace dlls::detectors::detect_face
