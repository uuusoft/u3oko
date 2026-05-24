/**
\file       block-mem-allocator-ext-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../mem-funcs-includes_int.hpp"
#include "block-mem-allocator.hpp"

extern "C" BOOST_SYMBOL_EXPORT
  utils::mem_funcs::IBlockMemAllocator::raw_ptr
  create_mem_impl ()
{
  return utils::mem_funcs::impl::instance ();
}


namespace utils::mem_funcs::impl
{
IBlockMemAllocator::raw_ptr
instance ()
{
  static BlockMemAllocator g_inst;
  return &g_inst;
}


BlockMemAllocator::BlockMemAllocator ()
{
  blocks_.reserve (consts::default_reserved_count_blocks);
}


BlockMemAllocator::~BlockMemAllocator ()
{
}


::libs::helpers::mem::IBlockMem::ptr
BlockMemAllocator::alloc (const size_type& size)
{
  lock_type                            lock (mtx_);
  ::libs::helpers::mem::IBlockMem::ptr exist = find_exist_block (size);

  if (exist)
  {
    exist->resize (size);
    return exist;
  }

  const std::size_t _real_size = std::max< size_type > (size, consts::min_size_block);
  BlockMem::ptr     _ret (new BlockMem (_real_size));

  blocks_.push_back (_ret);
  U3_ASSERT (blocks_.size () < consts::max_count_block);
  return _ret;
}


std::string
BlockMemAllocator::dump_memory_status ()
{
  lock_type lock (mtx_);
  return dump_status_int ();
}
}   // namespace utils::mem_funcs::impl
