#pragma once
/**
\file       imem.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
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
  U3_ADD_POINTERS_TO_SELF (IMem)
  U3_ADD_DELETE_MOVE_COPY (IMem)

  //  IMem interface
  virtual auto mem_alloc (std::int32_t, IBlockFakeMem::ptr) -> void*             = 0;
  virtual auto mem_free (IBlockFakeMem::ptr) -> bool                             = 0;
  virtual auto mem_atomic_call (IBlockFakeMem::cptr, const IHandlerMem&) -> bool = 0;

  protected:
  IMem ()          = default;
  virtual ~IMem () = default;
};
}   // namespace libs::link::mem
