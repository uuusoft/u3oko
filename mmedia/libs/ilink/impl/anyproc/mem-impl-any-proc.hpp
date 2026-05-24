#pragma once
/**
\file       mem-impl-any-proc.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

namespace libs::ilink::impl::anyproc
{
/// Релизация памяти для канала передачи данных
class MemImplAnyProc : public ::libs::link::mem::IMem
{
  public:
  MemImplAnyProc ();
  virtual ~MemImplAnyProc ();

  //  IMem impl
  virtual void* mem_alloc (int size, ::libs::link::mem::IBlockFakeMem::ptr hmem) override;
  virtual bool  mem_free (::libs::link::mem::IBlockFakeMem::ptr hmem) override;
  virtual bool  mem_atomic_call (::libs::link::mem::IBlockFakeMem::cptr hmem, const ::libs::link::mem::IHandlerMem& obj) override;
};
}   // namespace libs::ilink::impl::anyproc
