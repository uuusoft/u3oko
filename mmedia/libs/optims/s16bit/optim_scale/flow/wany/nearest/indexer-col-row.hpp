#pragma once
/**
\file       indexer-col-row.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_scale
*/

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
class IndexerColRow final
{
  public:
  IndexerColRow ();

  ~IndexerColRow ();

  ::libs::helpers::mem::IBlockMem::craw_ptr get_indxrow () const;
  ::libs::helpers::mem::IBlockMem::craw_ptr get_indxcol () const;

  void update (
    std::uint32_t src_width,
    std::uint32_t src_height,
    std::uint32_t src_stride,
    std::uint32_t dst_width,
    std::uint32_t dst_height);

  private:
  std::uint32_t                        src_width_;    //<
  std::uint32_t                        src_height_;   //<
  std::uint32_t                        src_stride_;   //<
  std::uint32_t                        dst_width_;    //<
  std::uint32_t                        dst_height_;   //<
  ::libs::helpers::mem::IBlockMem::ptr indxrow_;      //<
  ::libs::helpers::mem::IBlockMem::ptr indxcol_;      //<
};
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
