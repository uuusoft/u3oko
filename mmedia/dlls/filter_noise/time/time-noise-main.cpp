/**
\file       time-noise-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vfn_time ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::filter_noise::time::Filter);
  return ret;
}
