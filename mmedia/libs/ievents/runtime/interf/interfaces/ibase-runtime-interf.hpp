#pragma once
/**
\file       ibase-runtime-interf.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  virtual ~IBaseRuntimeInterf ()
  {
  }

  protected:
  IBaseRuntimeInterf ()
  {
  }
};
}   // namespace libs::ievents::runtime::interf::interfaces
