/**
\file       vcodec-gen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-gen-includes_int.hpp"
#include "vcodec-gen-info-filter-dll.hpp"
#include "vcodec-gen-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vdd_vcodec_gen ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret = new ::dlls::codecs::vcodec_gen::Filter;
  return ret;
}
