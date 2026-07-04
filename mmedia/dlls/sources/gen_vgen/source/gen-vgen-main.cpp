/**
\file       gen-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vsd_gen_vgen () -> ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
{
  return new ::dlls::sources::gen_vgen::Filter;
}
