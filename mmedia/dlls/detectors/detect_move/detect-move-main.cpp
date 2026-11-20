/**
\file       detect-move-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
*/
#include "detect-move-includes_int.hpp"
#include "detect-move-info-filter-dll.hpp"
#include "detect-move-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vdd_detect_move () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  return new ::dlls::detectors::detect_move::Filter;
}
