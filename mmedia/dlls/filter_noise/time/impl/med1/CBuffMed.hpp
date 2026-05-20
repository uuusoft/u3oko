#pragma once
/**
\file       CBuffMed.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

// EAI-REMOVE old shit
namespace dlls::filter_noise::time::impl::med1
{
#if 0
/// Буфер медианной фильтрации во временной области
class CBuffMed
{
  public:
  //  ext types
  using BuffMed1Impl node_type;

  explicit CBuffMed (int count_mbuf = ::libs::ievents::props::videos::noises::time::ext::consts::min_count_bufs);

  ~CBuffMed ();

  /// Функция синхронизации по текущему видекадру
  void sync_by_vbuf (const ::utils::dbufs::video::IVideoBuf::raw_ptr buf);
  /// Опциональная функция синхронизации по кадру разности
  void sync_by_dbuf (const ::utils::dbufs::video::IVideoBuf::raw_ptr buf);
  /// Функция возврата информации, связанной с указанным пикселем
  const node_type& get_node (std::size_t x, std::size_t y) const;


  private:
  //  internal types
  using std::vector< node_type > line_type;
  using std::vector< line_type > buf_type;

  buf_type              buf_;          //< узлы буфера
  CSharedInfoNodeBuffMed shared_info_;   //< разделяемая информация буфера между всеми пикселями
};
#endif
}   // namespace dlls::filter_noise::time::impl::med1
