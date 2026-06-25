#pragma once
/**
\file       iblock-fake-mem.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/

namespace libs::link::mem
{
class IBlockFakeMem
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockFakeMem)

  IBlockFakeMem ()          = default;
  virtual ~IBlockFakeMem () = default;
};
}   // namespace libs::link::mem
