/**
\file       vgen-conv3_11-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-conv3_11-includes_int.hpp"
#include "vgen-conv3_11-info-filter-dll.hpp"
#include "vgen-conv3_11-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vgd_vgen_conv3_11 ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::gens::vgen_conv3_11::Filter);
  return ret;
}
