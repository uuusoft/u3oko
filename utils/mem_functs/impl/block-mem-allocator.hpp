#pragma once
/**
\file       block-mem-allocator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/

namespace utils { namespace mem_functs { namespace impl { namespace consts {

const std::size_t min_size_block                = 32 * 1024;      //< Минимальный размер блока, который будет выделен.
const std::size_t max_count_block               = 1 * 512;        //< Максимальное количество одновременно выделенных блоков в одном процессе. Для отладки.
const std::size_t default_reserved_count_blocks = 1024;           //< ???

}}}}      // namespace utils::mem_functs::impl::consts


namespace utils { namespace mem_functs { namespace impl {
/**
  \brief  Функция-фабрика реализации.
  */
IBlockMemAllocator::raw_ptr instance ();
/**
\brief  Реализация интерфейса по управлению памятью в виде выровненных блоков.
*/
class BlockMemAllocator : public IBlockMemAllocator
{
  public:
  //  IBlockMemAllocator overrides
  virtual IBlockMem::ptr alloc (const size_type& _size) override;
  virtual void           dump_status () override;


  private:
  //  friends
  friend IBlockMemAllocator::raw_ptr instance ();
  //  int types
  using sync_type   = std::mutex;
  using guard_type  = std::lock_guard<sync_type>;
  using blocks_type = std::vector<BlockMem::ptr>;

  BlockMemAllocator ();

  virtual ~BlockMemAllocator ();

  IBlockMem::ptr find_exist_block (const size_type& _size);

  void dump_status_int ();

  sync_type   mtx_;         //< Поле для синхронизации доступа к объекту.
  blocks_type blocks_;      //< Список выделенных блоков памяти.
};

}}}      // namespace utils::mem_functs::impl
