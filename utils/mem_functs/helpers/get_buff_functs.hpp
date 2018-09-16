//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_buff_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      Файл вспомогательных функций по работы с буфером памяти, опирающихся на интерфейс IBlockMem
*/

namespace utils { namespace mem_functs { namespace helpers {

template <typename out_type>
out_type*
get_as (IBlockMem::raw_ptr _obj)
{
  return UUU_ALIGNED_MEM_CAST<out_type*> (_obj->get ());
}


template <typename out_type>
const out_type*
get_as (IBlockMem::craw_ptr _obj)
{
  return UUU_ALIGNED_MEM_CAST<const out_type*> (_obj->get ());
}

}}}      // namespace utils::mem_functs::helpers
