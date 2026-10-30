/**
\file       block-mem.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../mems-includes_int.hpp"
#include "block-mem.hpp"

namespace utils::mems::impl
{
BlockMem::BlockMem (const size_type size)
{
  ::libs::utility::checks::throw_ifn (size > 0, "BlockMem, zero size for alloc");
  details::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&buf_), size);
  ::libs::utility::checks::throw_ifn (buf_, "failed alloc buf");
  mem_size_ = size;
}


BlockMem::~BlockMem ()
{
  if (buf_)
  {
    details::u3free (::libs::utility::casts::reinterpret_cast_helper< void** > (&buf_));
    buf_      = nullptr;
    mem_size_ = 0;
  }
}


auto
BlockMem::get_int () -> std::uint8_t*
{
  ::libs::utility::checks::throw_ifn (buf_);
  return buf_;
}


auto
BlockMem::get_int () const -> const std::uint8_t*
{
  ::libs::utility::checks::throw_ifn (buf_);
  return buf_;
}


auto
BlockMem::get_capacity_int () const -> BlockMem::size_type
{
  return mem_size_;
}


auto
BlockMem::get_size_int () const -> BlockMem::size_type
{
  return data_size_;
}


void
BlockMem::set_size_int (BlockMem::size_type data_size)
{
  ::libs::utility::checks::throw_ifn (buf_);
  ::libs::utility::checks::throw_ifn (data_size_ <= mem_size_);
  ::libs::utility::checks::throw_ifn (data_size <= mem_size_);
  data_size_ = data_size;
}


void
BlockMem::resize_int (const BlockMem::size_type size)
{
  if (size <= mem_size_)
  {
    data_size_ = 0;
    return;
  }

  mem_size_  = 0;
  data_size_ = 0;

  details::u3realloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&buf_), size);
  ::libs::utility::checks::throw_ifn (buf_, "failed alloc buf");
  mem_size_ = size;
}
}   // namespace utils::mems::impl
