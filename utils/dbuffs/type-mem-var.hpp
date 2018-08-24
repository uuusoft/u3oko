#pragma once
/**
\file       type-mem-var.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       12.08.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief.
*/

namespace utils { namespace dbuffs {
/**
  \brief  Перечисление типов переменных, используемых для описания геометрии буфера.
  */
enum struct TypeMemVar
{
  size_data   = 0,      //< Размер данных в буфере.
  offset_data = 1,      //< Смещение данных относительно начала буфера.
  size_buffer = 2,      //< Полный размер памяти выделенной под буфер.
  max_bound   = 4       //< Максимальное значение данного типа для определения массивов под переменные.
};

}}      // namespace utils::dbuffs
