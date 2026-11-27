/**
\file       vgen-motion-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/
#include "vgen-motion-includes_int.hpp"
#include "vgen-motion-info-filter-dll.hpp"
#include "vgen-motion-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vgd_vgen_motion () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::gens::vgen_motion::Filter);
  return ret;
}
