#pragma once
/**
\file       system-darwin-property.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.10.2024
\project    u3_iproperties_lib
*/

#ifdef U3_OS_MACX_DESKTOP
namespace libs::iproperties::vers::system
{
class SystemDarwinProperty final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (SystemDarwinProperty)

  SystemDarwinProperty ()          = default;
  virtual ~SystemDarwinProperty () = default;

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
#endif
