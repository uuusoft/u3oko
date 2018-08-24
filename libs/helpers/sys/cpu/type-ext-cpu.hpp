#pragma once
/**
\file       type-ext-cpu.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Объявление различных типов расширений CPU.
*/

namespace libs { namespace helpers { namespace sys { namespace cpu {
/**
  \brief  Перечисление значимых для системы расширений CPU.
  */
enum struct TypeExtCpu
{
  usual    = 0,       //< Не определено, для общности.
  max      = 1,       //< Максимально поддерживаемое расширение.
  min      = 2,       //< Минмимально поддерживаемое расширение.
  alu      = 3,       //< Признак ALU (часто по умолчанию).
  mmx      = 4,       //< Признак MMX. Устарело depreceted.
  sse1     = 5,       //< Признак SSE1. Устарело depreceted.
  sse2     = 6,       //< Признак SSE2.
  sse3     = 7,       //< Признак SSE3.
  sse4_1   = 8,       //< Признак SSE4_1.
  sse4_2   = 9,       //< Признак SSE4_2.
  avx1     = 10,      //< Признак AVX1.
  axv2     = 11,      //< Признак AVX2.
  fma      = 12,      //< Признак FMA.
  f16c     = 13,      //< Признак F16C.
  rdrand   = 14,      //< Признак RDRAND.
  neon     = 15,      //< Признак NEON.
  hexagon4 = 16,      //< Признак Hexagon4.
  hexagon5 = 17,      //< Признак Hexagon5.
  hexagon6 = 18       //< Признак Hexagon6.
};

}}}}      // namespace libs::helpers::sys::cpu
