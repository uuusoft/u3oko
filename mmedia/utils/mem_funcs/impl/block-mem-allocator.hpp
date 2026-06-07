#pragma once
/**
\file       block-mem-allocator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
*/

namespace utils::mem_funcs::impl
{
IBlockMemAllocator::raw_ptr instance ();
/// Реализация интерфейса по управлению памятью в виде выровненных блоков
class BlockMemAllocator final : public IBlockMemAllocator
{
  public:
  //  IBlockMemAllocator overrides
  virtual ::libs::helpers::mem::IBlockMem::ptr alloc (const size_type& size) override;
  virtual std::string                          dump_memory_status () override;

  private:
  //  friends
  friend IBlockMemAllocator::raw_ptr instance ();
  //  internal typess
  using sync_type   = std::mutex;
  using lock_type   = std::scoped_lock< sync_type >;
  using blocks_type = std::vector< BlockMem::ptr >;

  BlockMemAllocator ();
  virtual ~BlockMemAllocator () = default;

  ::libs::helpers::mem::IBlockMem::ptr find_exist_block (const size_type& size);
  std::string                          dump_status_int ();

  sync_type   mtx_;      //< Поле для синхронизации доступа к объекту
  blocks_type blocks_;   //< Список выделенных блоков памяти
};
}   // namespace utils::mem_funcs::impl
