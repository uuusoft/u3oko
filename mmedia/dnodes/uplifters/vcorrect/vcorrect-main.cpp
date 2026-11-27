/**
\file       vcorrect-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\brief      Модуль базовой коррекции изображения
*/
#include "vcorrect-includes_int.hpp"
#include "vcorrect-info-filter-dll.hpp"
#include "vcorrect-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vdd_vcorrect () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::uplifters::vcorrect::Filter);
  return ret;
}
