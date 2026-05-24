#pragma once
/**
\file       shared-info-node-buf.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med3
{
/// Разделяемая в режиме r/o информация между всеми узлами буфера
struct SharedInfoNodeBuff final {
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SharedInfoNodeBuff)

  SharedInfoNodeBuff () :
    params_ (nullptr),
    count_akk_mbuf_ (0)
  {
  }

  syn::MedianTimeFilterProp::raw_ptr    params_;           //<Параметры фильтрации
  std::uint32_t                         count_akk_mbuf_;   //<Количество накопленных на данный момент буферов
  ::utils::dbufs::video::IVideoBuf::ptr akk_mbuf_;         //<Буфер-сумма буферов
};
}   // namespace dlls::filter_noise::time::impl::med3
