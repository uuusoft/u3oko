/**
\file       block-mem-allocator-int-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_mem_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../mem-funcs-includes_int.hpp"
#include "block-mem-allocator.hpp"

namespace utils::mem_funcs::impl
{
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
         std::to_string (U3_CAST_STATIC< float > (size_use_mem) / (size_all_mem ? size_all_mem : 1));
}
}   // namespace utils::mem_funcs::impl
