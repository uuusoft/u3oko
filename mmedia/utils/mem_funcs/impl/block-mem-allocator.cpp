/**
\file       block-mem-allocator.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mem_funcs
*/
#include "../mem-funcs-includes_int.hpp"
#include "block-mem-allocator.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_mem_impl () -> utils::mem_funcs::IBlockMemAllocator::raw_ptr
{
  return utils::mem_funcs::impl::instance ();
}

namespace utils::mem_funcs::impl
{
auto
instance () -> IBlockMemAllocator::raw_ptr
{
  static BlockMemAllocator g_inst;
  return &g_inst;
}


BlockMemAllocator::BlockMemAllocator ()
{
  blocks_.reserve (consts::default_reserved_count_blocks);
}


inline auto
get_abs_diff (const std::size_t& size1, const std::size_t& size2) -> std::size_t
{
  return size1 > size2 ? size1 - size2 : size2 - size1;
}


auto
BlockMemAllocator::find_exist_block (const size_type& size) -> syn::IBlockMem::ptr
{
  syn::IBlockMem::ptr candidate;
  std::size_t         cand_diff = 0;

  for (BlockMem::ptr& _block : blocks_)
  {
    if (_block.use_count () > 1)
    {
      continue;
    }

    const auto _block_size = _block->get_capacity ();
    if (_block_size < size)
    {
      continue;
    }

    if (!candidate)
    {
      candidate = _block;
      cand_diff = get_abs_diff (_block_size, size);
    }
    else
    {
      auto cur_diff = get_abs_diff (_block_size, size);
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


auto
BlockMemAllocator::dump_status_int () -> std::string
{
  const auto   _count_all_blocks = blocks_.size ();
  auto         _count_use_blocks = 0;
  std::int64_t size_all_mem      = 0;
  std::int64_t size_use_mem      = 0;

  for (auto& _block : blocks_)
  {
    const auto _mem_block = _block->get_capacity ();
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


auto
BlockMemAllocator::alloc (const size_type& size) -> syn::IBlockMem::ptr
{
  lock_type           lock (mtx_);
  syn::IBlockMem::ptr exist = find_exist_block (size);
  if (exist)
  {
    exist->resize (size);
    return exist;
  }

  const std::size_t real_size = std::max< size_type > (size, consts::min_size_block);
  blocks_.emplace_back (std::make_shared< BlockMem > (real_size));
  U3_ASSERT (blocks_.size () < consts::max_count_block);
  return blocks_.back ();
}


auto
BlockMemAllocator::dump_memory_status () -> std::string
{
  lock_type lock (mtx_);
  return dump_status_int ();
}
}   // namespace utils::mem_funcs::impl
