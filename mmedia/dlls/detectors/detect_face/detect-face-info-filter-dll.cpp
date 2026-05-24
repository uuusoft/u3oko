/**
\file       detect-face-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_detect_face
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"

namespace dlls::detectors::detect_face
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr)
{
  init ();
}


InfoFilter::~InfoFilter ()
{
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoDetectProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));

#ifndef U3_SKIP_DLIB
  detector_ = dlib::get_frontal_face_detector ();
#endif
}
}   // namespace dlls::detectors::detect_face
