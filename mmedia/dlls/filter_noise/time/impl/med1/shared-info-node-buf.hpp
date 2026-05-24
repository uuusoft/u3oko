#pragma once
/**
\file       shared-info-node-buf.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med1
{
/// Разделяемая в режиме r/o информация между всеми узлами буфера
struct CSharedInfoNodeBuffMed final {
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CSharedInfoNodeBuffMed)

  CSharedInfoNodeBuffMed () :
    count_mbuf_ (0),
    count_akk_mbuf_ (0)
  {
  }

  int count_mbuf_;       //< максимальное количество буферов во временной области, участвующее в фильтрации
  int count_akk_mbuf_;   //< количество накопленных буферов
};
}   // namespace dlls::filter_noise::time::impl::med1
