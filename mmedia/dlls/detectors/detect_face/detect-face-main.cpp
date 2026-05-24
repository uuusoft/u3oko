/**
\file       detect-face-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_face
\brief      Модуль детекции лица на основе dlib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vdd_detect_face ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::detectors::detect_face::Filter);
  return ret;
}
