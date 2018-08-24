//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       block-mem-allocator-proxy-int-functs.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "block-mem-allocator.hpp"

namespace utils { namespace mem_functs { namespace impl {

inline std::size_t
get_diff (const std::size_t& _size1, const std::size_t& _size2)
{
  return _size1 > _size2 ? _size1 - _size2 : _size2 - _size1;
}


IBlockMem::ptr
BlockMemAllocator::find_exist_block (const size_type& _size)
{
  IBlockMem::ptr _candidate;
  std::size_t    _cand_diff = 0;

  for (BlockMem::ptr& _block : blocks_)
    {
      if (_block.use_count () > 1)
        {
          //  Блок используется.
          continue;
        }

      if (!_candidate)
        {
          _candidate = _block;
          _cand_diff = get_diff (_candidate->get_buff_size (), _size);
        }
      //  Ищем как можно лучшего кандидата - с минимальным отличием по требуемому размеру памяти.
      auto _cur_diff = get_diff (_block->get_buff_size (), _size);
      if (_cur_diff < _cand_diff)
        {
          _candidate = _block;
          _cand_diff = _cur_diff;
        }

      if (0 == _cand_diff)
        {
          //  Иделальное совпадение по размеру - сразу выходим.
          return _candidate;
        }
    }

  return _candidate;
}


void
BlockMemAllocator::dump_status_int ()
{
  XULOG_INFO ("BlockMemAllocator::dump_status_int: beg");
  const auto       _count_all_blocks = blocks_.size ();
  auto             _count_use_blocks = 0;
  signed long long _size_all_mem     = 0;
  signed long long _size_use_mem     = 0;

  for (auto& _block : blocks_)
    {
      const auto _mem_block = _block->get_buff_size ();
      if (_block.use_count () > 1)
        {
          _size_use_mem += _mem_block;
          ++_count_use_blocks;
        }
      _size_all_mem += _mem_block;
    }

  XULOG_INFO ("   count_use_blocks / count_all_blocks:" << _count_use_blocks << " / " << _count_all_blocks);
  XULOG_INFO ("   size_use_mem / size_all_mem: " << _size_use_mem << " / " << _size_all_mem);
  XULOG_INFO ("BlockMemAllocator::dump_status_int: end");
  return;
}

}}}      // namespace utils::mem_functs::impl
