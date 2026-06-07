/**
\file       all2rgb-dll-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_all2rgb
\brief      Модуль преобразования всех форматов в RGB24
*/
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vcd_all2rgb ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::convertors::all2rgb::Filter);
  return ret;
}
