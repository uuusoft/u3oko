//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buff-allocator.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Реализация интерфейся для выделения буферов под видео/аудио данные.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"

#include "buff-allocator.hpp"
#include "mmedia/utils/dbuffs/video/impl/video-buff.hpp"

namespace utils { namespace dbuffs { namespace allocator {

BuffAllocator*
BuffAllocator::instance ()
{
  static BuffAllocator* _impl (new BuffAllocator ());      //  Никогда не удаляем.
  return _impl;
}


BuffAllocator::BuffAllocator () :
  counter_alloc_buffers_ (0),
  counter_reuse_buffers_ (0)
{}


BuffAllocator::~BuffAllocator ()
{
  XULOG_INFO ("BuffAllocator::~BuffAllocator: beg");
  clear ();
  XULOG_INFO ("BuffAllocator::~BuffAllocator: end");
}


utils::dbuffs::video::IVideoBuff::ptr
BuffAllocator::get ()
{
  guard_type _grd (mtx_);

  for (const utils::dbuffs::video::IVideoBuff::ptr& _buff : buffs_)
    {
      //  найден уже выделенный и уже не используемый клиентом буфер.
      if (_buff.use_count () <= 1)
        {
          _buff->set_flag (::utils::dbuffs::TypeFlagsBuff::empty, true);
          ++counter_reuse_buffers_;
          return _buff;
        }
    }
  //  выделяем новый буфер.
  utils::dbuffs::video::IVideoBuff::ptr _new (new utils::dbuffs::video::impl::VideoBuff ());
  buffs_.push_back (_new);
  ++counter_alloc_buffers_;
  return _new;
}


void
BuffAllocator::clear ()
{
  XULOG_INFO ("BuffAllocator::clear: beg");
  guard_type _grd (mtx_);
  dump_state_int ();

  for (utils::dbuffs::video::IVideoBuff::ptr& _buff : buffs_)
    {
      UASSERT (_buff.use_count () <= 1);
      _buff->set_flag (::utils::dbuffs::TypeFlagsBuff::empty, true);
      _buff.reset ();
    }
  buffs_.clear ();
  counter_alloc_buffers_ = 0;
  counter_reuse_buffers_ = 0;
  XULOG_INFO ("BuffAllocator::clear: end");
  return;
}


void
BuffAllocator::dump_state ()
{
  guard_type _grd (mtx_);
  dump_state_int ();
  return;
}


void
BuffAllocator::dump_state_int ()
{
  XULOG_INFO ("BuffAllocator::dump_state_int: beg");
  signed long long _all_mem         = 0;
  signed long long _use_mem         = 0;
  signed long long _count_use_buffs = 0;
  const auto       _count_all_buffs = buffs_.size ();

  for (const utils::dbuffs::video::IVideoBuff::ptr& _buff : buffs_)
    {
      auto _mem_buff = (*_buff)[::utils::dbuffs::TypeMemVar::size_buffer];
      if (_buff.use_count () > 1)
        {
          _use_mem += _mem_buff;
          ++_count_use_buffs;
        }
      _all_mem += _mem_buff;
    }

  XULOG_INFO ("   count_use_buffs / count_all_buffs: " << _count_use_buffs << " / " << _count_all_buffs);
  XULOG_INFO ("   use_mem / all_mem: " << _use_mem << " / " << _all_mem);
  XULOG_INFO ("   counter_reuse_buffers / counter_alloc_buffers: " << counter_reuse_buffers_ << " / " << counter_alloc_buffers_);
  XULOG_INFO ("BuffAllocator::dump_state_int: end");
  return;
}

}}}      // namespace utils::dbuffs::allocator

BOOST_DLL_ALIAS (utils::dbuffs::allocator::BuffAllocator::instance, instance_buff_allocator);
