#pragma once
/**
\file       ibase-runtime-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       18.04.2022
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::interf::interfaces
{
class IBaseRuntimeInterf
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IBaseRuntimeInterf)

  virtual ~IBaseRuntimeInterf () = default;

  protected:
  IBaseRuntimeInterf () = default;
};
}   // namespace libs::events_base::runtime::interf::interfaces
