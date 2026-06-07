#pragma once
/**
\file       block-mem.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
*/

namespace utils::mem_funcs::impl
{
///  Реализация работы с блоком памяти
class BlockMem final : public ::libs::helpers::mem::IBlockMem
{
  public:
  using size_type = ::libs::helpers::mem::IBlockMem::size_type;

  BlockMem (const BlockMem::size_type);
  virtual ~BlockMem ();

  private:
  // ::libs::helpers::mem:: IBlockMem overrides
  virtual std::uint8_t*       get_int () override;
  virtual const std::uint8_t* get_int () const override;
  virtual BlockMem::size_type get_buf_size_int () const override;
  virtual BlockMem::size_type get_data_size_int () const override;
  virtual void                set_data_size_int (size_type) override;
  virtual void                resize_int (size_type) override;

  void reset_memory ();

  std::uint8_t* buf_       = nullptr;   //< Сырой блок памяти
  size_type     size_      = 0;         //< Размер сырого блока памяти
  size_type     data_size_ = 0;         //< Размер данных в блоке
};
}   // namespace utils::mem_funcs::impl
