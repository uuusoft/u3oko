#pragma once
/**
\file       imem.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
*/

namespace libs::link::mem
{
/// Опиональный интерфейс памяти
/// Если он предоставляется объектом-связью, то для передачи блоков данных нужно использовать его
class IMem
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IMem)

  IMem (const IMem&)            = delete;
  IMem& operator= (const IMem&) = delete;

  //  IMem interface
  virtual void* mem_alloc (int, IBlockFakeMem::ptr)                       = 0;
  virtual bool  mem_free (IBlockFakeMem::ptr)                             = 0;
  virtual bool  mem_atomic_call (IBlockFakeMem::cptr, const IHandlerMem&) = 0;

  protected:
  IMem ()          = default;
  virtual ~IMem () = default;
};
}   // namespace libs::link::mem
