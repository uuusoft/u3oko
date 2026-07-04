/**
\file       doptim-dll-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_doptim_dll
\brief      Модуль доступа к реализациям алгоритмов обработки данных
*/
#include "doptim-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vdd_doptim () -> ::libs::optim::io::IOptim::raw_ptr
{
  static ::dlls::doptim::impl::IOptimImpl ret;
  return &ret;
}
