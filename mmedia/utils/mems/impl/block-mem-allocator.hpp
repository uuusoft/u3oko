#pragma once
/**
\file       block-mem-allocator.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mems
*/

namespace utils::mems::impl
{
IBlockMemAllocator::raw_ptr instance ();
/// Реализация интерфейса по управлению памятью в виде выровненных блоков
class BlockMemAllocator final : public IBlockMemAllocator
{
  public:
  //  IBlockMemAllocator overrides
  virtual auto alloc (const size_type& size) -> syn::IBlockMem::ptr override;
  virtual auto dump_memory_status () -> std::string override;

  private:
  //  friends
  friend IBlockMemAllocator::raw_ptr instance ();
  //  internal typess
  using sync_type   = std::mutex;
  using lock_type   = std::scoped_lock< sync_type >;
  using blocks_type = std::vector< BlockMem::ptr >;

  BlockMemAllocator ();
  virtual ~BlockMemAllocator () = default;

  auto find_exist_block (const size_type& size) -> syn::IBlockMem::ptr;
  auto dump_status_int () -> std::string;

  sync_type   mtx_;      //< Поле для синхронизации доступа к объекту
  blocks_type blocks_;   //< Список выделенных блоков памяти
};
}   // namespace utils::mems::impl
