/**
\file       base_id-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_base_id_dll
\brief      Модуль идентификации камеры и контроля частоты потоков фреймов в ней
*/
#include "base_id-includes_int.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vdd_base_id () -> ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::base_id::Filter);
  return ret;
}
