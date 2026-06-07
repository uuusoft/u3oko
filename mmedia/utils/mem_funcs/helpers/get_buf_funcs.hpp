#pragma once
/**
\file       get_buf_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_mem_funcs
\brief      Файл вспомогательных функций по работы с буфером памяти, опирающихся на интерфейс IBlockMem
*/

namespace utils::mem_funcs::helpers
{
template< typename out_type >
out_type*
get_as (::libs::helpers::mem::IBlockMem::raw_ptr _obj)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< out_type* > (_obj->get ());
}


template< typename out_type >
const out_type*
get_as (::libs::helpers::mem::IBlockMem::craw_ptr _obj)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< const out_type* > (_obj->get ());
}
}   // namespace utils::mem_funcs::helpers
