/**
\file       detect-face-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_detect_face
\brief      Модуль детекции лица на основе dlib
*/
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vdd_detect_face ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::detectors::detect_face::Filter);
  return ret;
}
