/**
\file       doptim-dll-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_doptim_dll
\brief      Модуль доступа к реализациям алгоритмов обработки данных
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "doptim-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::optim::io::IOptim::raw_ptr
create_impl_vdd_doptim ()
{
  static ::dlls::doptim::impl::IOptimImpl ret;
  return &ret;
}
