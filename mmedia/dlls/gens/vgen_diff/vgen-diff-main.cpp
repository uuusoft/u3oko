/**
\file       vgen-diff-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff
*/
#include "vgen-diff-includes_int.hpp"
#include "vgen-diff-info-filter-dll.hpp"
#include "vgen-diff-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vgd_vgen_diff () -> ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::gens::vgen_diff::Filter);
  return ret;
}
