/**
\file       all2hsl-dll-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\brief      Модуль преобразование RGB24->HSL
*/
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vcd_all2hsl () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::convertors::all2hsl::Filter);
  return ret;
}
