#pragma once
/**
\file       buf-med3impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me

\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med3
{
/**
\brief  Буфер медианной фильтрации во временной области.
*/
class BuffMed3Impl final
{
  public:
  explicit BuffMed3Impl (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::raw_ptr params = nullptr);

  ~BuffMed3Impl ();

  /// Функция синхронизации по текущему видекадру
  void sync_by_vbuf (
    const ::utils::dbufs::video::IVideoBuf::raw_ptr                                   buf,
    const ::utils::dbufs::video::IVideoBuf::raw_ptr                                   dbuf,
    ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::craw_ptr impl_info);


  private:
  SharedInfoNodeBuff shared_info_;   //< разделяемая информация буфера между всеми пикселями
};
}   // namespace dlls::filter_noise::time::impl::med3
