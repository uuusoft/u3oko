/**
\file   main.cpp
\brief  Стандартная обработка сообщений от системы - практически едина для всех реализаций данного вида DLL
\brief  отличие состоит в типе создаваемеого объекта
\author Erashov Anton erashov2026@proton.me
\date   26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
create_impl_vdd_vmatrix ()
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::uplifters::vmatrix::Filter);
  return ret;
}
