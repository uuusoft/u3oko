//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       block-mem.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "block-mem.hpp"

namespace utils { namespace mem_functs { namespace impl {

BlockMem::BlockMem (const std::size_t _size) :
  buff_ (nullptr),
  size_ (_size),
  data_size_ (0)
{
  CHECK_STATE (size_ > 0, "BlockMem, zero size for alloc");
  details::aalloc (UUU_CONVERT2VOID (&buff_), size_);
  UASSERT (buff_);
  reset_memory ();
}


BlockMem::~BlockMem ()
{
  if (!buff_)
    {
      return;
    }

  details::afree (UUU_CONVERT2VOID (&buff_));
  buff_ = nullptr;
}


unsigned char*
BlockMem::get_int ()
{
  UASSERT (buff_);
  return buff_;
}


const unsigned char*
BlockMem::get_int () const
{
  UASSERT (buff_);
  return buff_;
}


std::size_t
BlockMem::get_buff_size_int () const
{
  UASSERT (buff_);
  return size_;
}


std::size_t
BlockMem::get_data_size_int () const
{
  UASSERT (buff_);
  return data_size_;
}


void
BlockMem::set_data_size_int (std::size_t _data_size)
{
  UASSERT (buff_);
  UASSERT (data_size_ <= size_);
  UASSERT (_data_size <= size_);
  data_size_ = _data_size;
  return;
}


void
BlockMem::resize_int (const std::size_t _size)
{
  if (_size <= size_)
    {
      return;
    }

  size_      = _size;
  data_size_ = 0;
  details::arealloc (UUU_CONVERT2VOID (&buff_), size_);
  return;
}


void
BlockMem::reset_memory ()
{
  if (!buff_ || 0 == size_)
    {
      return;
    }
#if defined(UUU_FORCE_RESET_MEMORY_AFTER_ALLOC)
  memset (buff_, consts::filling, size_);
#endif
  return;
}

}}}      // namespace utils::mem_functs::impl
