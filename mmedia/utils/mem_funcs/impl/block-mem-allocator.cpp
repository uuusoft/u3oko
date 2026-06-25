/**
\file       block-mem-allocator.cpp
\author     Erashov Anton erashov2026@proton.me
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


inline std::size_t
get_diff (const std::size_t& size1, const std::size_t& size2)
{
  return size1 > size2 ? size1 - size2 : size2 - size1;
}


::libs::helpers::mem::IBlockMem::ptr
BlockMemAllocator::find_exist_block (const size_type& size)
{
  ::libs::helpers::mem::IBlockMem::ptr candidate;
  std::size_t                          cand_diff = 0;

  for (BlockMem::ptr& _block : blocks_)
  {
    if (_block.use_count () > 1)
    {
      continue;
    }

    const auto _block_size = _block->get_buf_size ();
    if (_block_size < size)
    {
      continue;
    }

    if (!candidate)
    {
      candidate = _block;
      cand_diff = get_diff (_block_size, size);
    }
    else
    {
      auto cur_diff = get_diff (_block_size, size);
      if (cur_diff < cand_diff)
      {
        candidate = _block;
        cand_diff = cur_diff;
      }
    }

    if (0 == cand_diff)
    {
      return candidate;
    }
  }
  return candidate;
}


std::string
BlockMemAllocator::dump_status_int ()
{
  const auto   _count_all_blocks = blocks_.size ();
  auto         _count_use_blocks = 0;
  std::int64_t size_all_mem      = 0;
  std::int64_t size_use_mem      = 0;

  for (auto& _block : blocks_)
  {
    const auto _mem_block = _block->get_buf_size ();
    if (_block.use_count () > 1)
    {
      size_use_mem += _mem_block;
      ++_count_use_blocks;
    }
    size_all_mem += _mem_block;
  }

  return std::to_string (size_all_mem) + " bytes {" + std::to_string (_count_all_blocks) + "}, " +
         std::to_string (size_use_mem) + " {" + std::to_string (_count_use_blocks) + "} koeff " +
         std::to_string (U3_CAST_FLOAT (size_use_mem) / (size_all_mem ? size_all_mem : 1));
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
