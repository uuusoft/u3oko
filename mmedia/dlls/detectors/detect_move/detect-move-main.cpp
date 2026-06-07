/**
\file       detect-move-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_move
*/
#include "detect-move-includes_int.hpp"
#include "detect-move-info-filter-dll.hpp"
#include "detect-move-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vdd_detect_move ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::detectors::detect_move::Filter);
  return ret;
}
