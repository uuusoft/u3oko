#pragma once
/**
\file       get_buf_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_mem_funcs
\brief      Файл вспомогательных функций по работы с буфером памяти, опирающихся на интерфейс IBlockMem
*/

namespace utils::mem_funcs::helpers
{
template< typename TType >
TType*
get_as (::libs::utility::mem::IBlockMem::raw_ptr obj)
{
  return ::libs::utility::casts::reinterpret_cast_helper< TType* > (obj->get ());
}


template< typename TType >
const TType*
get_as (::libs::utility::mem::IBlockMem::craw_ptr obj)
{
  return ::libs::utility::casts::reinterpret_cast_helper< const TType* > (obj->get ());
}
}   // namespace utils::mem_funcs::helpers
