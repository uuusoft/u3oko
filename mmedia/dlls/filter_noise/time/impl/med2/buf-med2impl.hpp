#pragma once
/**
\file       buf-med2impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med2
{
// forward
class Med2Impl;
using MedianTimeFilterProp = ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp;

/// Буфер медианной фильтрации во временной области
class BuffMed2Impl final
{
  friend class Med2Impl;

  public:
  explicit BuffMed2Impl (MedianTimeFilterProp::raw_ptr params = nullptr);

  ~BuffMed2Impl ();
  /// Основая функция фильтрации кадра
  /// Может (и должна) безопасно выполнятся одновременно в нескольких потоках
  void sync_by_vbuf (
    ::libs::optim::io::ProxyBuf*       buf,
    ::libs::optim::io::ProxyBuf*       akk_mbuf,
    const ::libs::optim::io::ProxyBuf* dbuf,
    MedianTimeFilterProp::craw_ptr     impl_info) const;

  /// Функция синхронизации внутренних буферов и структур с внешним буфером, который требуется фильтровать
  void update_int_bufs (
    ::libs::optim::io::ProxyBuf*       buf,
    const ::libs::optim::io::ProxyBuf* dbuf,
    MedianTimeFilterProp::craw_ptr     impl_info);

  private:
  SharedInfoNodeBuff shared_info_;   //< разделяемая информация буфера между всеми пикселями
};
}   // namespace dlls::filter_noise::time::impl::med2
