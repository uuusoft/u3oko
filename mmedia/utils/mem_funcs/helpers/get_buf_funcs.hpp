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
template< typename TTOut >
TTOut*
get_as (::libs::utility::mem::IBlockMem::raw_ptr obj)
{
  return ::libs::utility::casts::reinterpret_cast_helper< TTOut* > (obj->get ());
}


template< typename TTOut >
const TTOut*
get_as (::libs::utility::mem::IBlockMem::craw_ptr obj)
{
  return ::libs::utility::casts::reinterpret_cast_helper< const TTOut* > (obj->get ());
}
}   // namespace utils::mem_funcs::helpers
