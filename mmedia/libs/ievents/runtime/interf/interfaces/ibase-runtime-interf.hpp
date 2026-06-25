#pragma once
/**
\file       ibase-runtime-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       18.04.2022
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf::interfaces
{
class IBaseRuntimeInterf
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBaseRuntimeInterf)

  virtual ~IBaseRuntimeInterf () = default;

  protected:
  IBaseRuntimeInterf () = default;
};
}   // namespace libs::ievents::runtime::interf::interfaces
