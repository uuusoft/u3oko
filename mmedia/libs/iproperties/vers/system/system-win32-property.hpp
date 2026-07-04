#pragma once
/**
\file       system-win32-property.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::vers::system
{
class SystemWin32Property final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (SystemWin32Property)

  SystemWin32Property ()          = default;
  virtual ~SystemWin32Property () = default;

  private:
  virtual bool
  self_test_int () const override
  {
    return true;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }
};
}   // namespace libs::iproperties::vers::system
