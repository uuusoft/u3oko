#pragma once
/**
\file       buf-med3impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med3
{
/// Буфер медианной фильтрации во временной области
class BuffMed3Impl final
{
  public:
  explicit BuffMed3Impl (syn::MedianTimeFilterProp::raw_ptr params = nullptr);

  ~BuffMed3Impl ();

  /// Функция синхронизации по текущему видекадру
  void sync_by_vbuf (
    const ::utils::dbufs::video::IVideoBuf::raw_ptr buf,
    const ::utils::dbufs::video::IVideoBuf::raw_ptr dbuf,
    syn::MedianTimeFilterProp::craw_ptr             impl_info);

  private:
  SharedInfoNodeBuff shared_info_;   //< разделяемая информация буфера между всеми пикселями
};
}   // namespace dlls::filter_noise::time::impl::med3
