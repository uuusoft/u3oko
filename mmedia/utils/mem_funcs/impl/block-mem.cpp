/**
\file       block-mem.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_mem_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../mem-funcs-includes_int.hpp"
#include "block-mem.hpp"

//  Макрос включает принудительный сброс памяти в utils::mem_funcs::consts::filling после перераспределения. Используется для отладки.
#if defined(U3_CNTRL_DEBUG) && 0
#  ifndef U3_CLEAR_BLOCK_MEM_AFTER_ALLOC
#    define U3_CLEAR_BLOCK_MEM_AFTER_ALLOC
#  endif
#endif

namespace utils::mem_funcs::impl
{
BlockMem::BlockMem (const size_type size) :
  buf_ (nullptr),
  size_ (0),
  data_size_ (0)
{
  U3_CHECK (size > 0, "BlockMem, zero size for alloc");
  details::aalloc (U3_CAST_2VOID (&buf_), size);
  U3_CHECK (buf_, "failed alloc buf");
  // U3_ASSERT (buf_);
  size_ = size;
  reset_memory ();
}


BlockMem::~BlockMem ()
{
  if (!buf_)
  {
    return;
  }

  details::afree (U3_CAST_2VOID (&buf_));
  buf_  = nullptr;
  size_ = 0;
}


std::uint8_t*
BlockMem::get_int ()
{
  U3_ASSERT (buf_);
  return buf_;
}


const std::uint8_t*
BlockMem::get_int () const
{
  U3_ASSERT (buf_);
  return buf_;
}


BlockMem::size_type
BlockMem::get_buf_size_int () const
{
  return size_;
}


BlockMem::size_type
BlockMem::get_data_size_int () const
{
  return data_size_;
}


void
BlockMem::set_data_size_int (BlockMem::size_type data_size)
{
  U3_ASSERT (buf_);
  U3_ASSERT (data_size_ <= size_);
  U3_ASSERT (data_size <= size_);
  data_size_ = data_size;
}


void
BlockMem::resize_int (const BlockMem::size_type size)
{
  if (size <= size_)
  {
    data_size_ = 0;
    return;
  }

  size_      = 0;
  data_size_ = 0;
  details::arealloc (U3_CAST_2VOID (&buf_), size);
  U3_CHECK (buf_, "failed alloc buf");
  size_ = size;
}


void
BlockMem::reset_memory ()
{
  if (!buf_ || 0 == size_)
  {
    return;
  }

#if defined(U3_CLEAR_BLOCK_MEM_AFTER_ALLOC)
  memset (buf_, consts::filling, size_);
#endif
}
}   // namespace utils::mem_funcs::impl
