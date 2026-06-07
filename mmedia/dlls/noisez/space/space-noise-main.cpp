/**
\file       space-noise-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_filter_space
*/
#include "space-noise-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vfn_space ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::noisez::space::Filter);
  return ret;
}
