/**
\file       all2hsl-dll-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_all2hsl
\brief      Модуль преобразование RGB24->HSL.
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vcd_all2hsl ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::convertors::all2hsl::Filter);
  return ret;
}
