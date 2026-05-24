/**
\file       vgen-mops-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2017
\project    u3_vgen_mops
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-includes_int.hpp"
#include "vgen-mops-info-filter-dll.hpp"
#include "vgen-mops-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vgd_vgen_mops ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::gens::vgen_mops::Filter);
  return ret;
}
