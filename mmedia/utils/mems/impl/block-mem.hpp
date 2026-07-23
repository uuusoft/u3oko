#pragma once
/**
\file       block-mem.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mems
*/

namespace utils::mems::impl::syn
{
using IBlockMem = ::libs::utility::mem::IBlockMem;
}

namespace utils::mems::impl
{
///  Реализация блока памяти
class BlockMem final : public syn::IBlockMem
{
  public:
  using size_type = syn::IBlockMem::size_type;

  BlockMem (const BlockMem::size_type);
  virtual ~BlockMem ();

  private:
  // syn::IBlockMem overrides
  virtual auto get_int () -> std::uint8_t* override;
  virtual auto get_int () const -> const std::uint8_t* override;
  virtual auto get_capacity_int () const -> BlockMem::size_type override;
  virtual auto get_size_int () const -> BlockMem::size_type override;
  virtual auto set_size_int (size_type) -> void override;
  virtual auto resize_int (size_type) -> void override;

  std::uint8_t* buf_ { nullptr };   //< Сырой блок памяти
  size_type     mem_size_ { 0 };    //< Размер сырого блока памяти
  size_type     data_size_ { 0 };   //< Размер данных в блоке
};
}   // namespace utils::mems::impl
