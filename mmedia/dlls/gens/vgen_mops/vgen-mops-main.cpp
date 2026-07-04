/**
\file       vgen-mops-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2017
\project    u3_vgen_mops
*/
#include "vgen-mops-includes_int.hpp"
#include "vgen-mops-info-filter-dll.hpp"
#include "vgen-mops-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vgd_vgen_mops () -> ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::gens::vgen_mops::Filter);
  return ret;
}
