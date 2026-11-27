/**
\file       space-noise-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/
#include "space-noise-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vfn_space () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::noisez::space::Filter);
  return ret;
}
