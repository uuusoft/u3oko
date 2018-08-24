//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       block-mem-allocator-ext-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "block-mem-allocator.hpp"

namespace utils { namespace mem_functs { namespace impl {

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
{}


IBlockMem::ptr
BlockMemAllocator::alloc (const size_type& _size)
{
  guard_type     _grd (mtx_);
  IBlockMem::ptr _exist = find_exist_block (_size);

  if (_exist)
    {
      _exist->resize (_size);
      return _exist;
    }

  const std::size_t _real_size = std::max<std::size_t> (_size, consts::min_size_block);      // Т.к. память используется для данных большого размера, гарантируем минимальный размер для улучшения повторного использования.
  BlockMem::ptr     _ret (new BlockMem (_real_size));

  blocks_.push_back (_ret);
  UASSERT (blocks_.size () < consts::max_count_block);
  return _ret;
}


void
BlockMemAllocator::dump_status ()
{
  guard_type _grd (mtx_);
  dump_status_int ();
  return;
}

}}}      // namespace utils::mem_functs::impl

BOOST_DLL_ALIAS (::utils::mem_functs::impl::instance, instance_block_mem);
