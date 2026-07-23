/**
\file       block-mem-allocator.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mems
*/
#include "../mems-includes_int.hpp"
#include "block-mem-allocator.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_mem_impl () -> utils::mems::IBlockMemAllocator::raw_ptr
{
  return utils::mems::impl::instance ();
}

namespace utils::mems::impl
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
  syn::IBlockMem::ptr ret;
  std::size_t         difference { 0 };

  for (BlockMem::ptr& block : blocks_)
  {
    if (block.use_count () > 1)
    {
      continue;
    }

    const auto block_size = block->get_capacity ();
    if (block_size < size)
    {
      continue;
    }

    if (!ret)
    {
      ret        = block;
      difference = get_abs_diff (block_size, size);
    }
    else
    {
      auto this_difference = get_abs_diff (block_size, size);
      if (this_difference < difference)
      {
        ret        = block;
        difference = this_difference;
      }
    }
    if (0 == difference)
    {
      return ret;
    }
  }
  return ret;
}


auto
BlockMemAllocator::dump_status_int () -> std::string
{
  const auto   count_all_blocks = blocks_.size ();
  auto         count_use_blocks = 0;
  std::int64_t size_all_mem     = 0;
  std::int64_t size_use_mem     = 0;

  for (auto& _block : blocks_)
  {
    const auto _mem_block = _block->get_capacity ();
    if (_block.use_count () > 1)
    {
      size_use_mem += _mem_block;
      ++count_use_blocks;
    }
    size_all_mem += _mem_block;
  }

  return std::to_string (size_all_mem) + " bytes {" + std::to_string (count_all_blocks) + "}, " +
         std::to_string (size_use_mem) + " {" + std::to_string (count_use_blocks) + "} koeff " +
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
}   // namespace utils::mems::impl
