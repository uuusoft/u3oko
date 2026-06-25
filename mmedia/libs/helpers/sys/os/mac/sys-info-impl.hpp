#pragma once
/**
\file       sys-info-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

#ifdef U3_OS_MACX_DESKTOP
namespace libs::helpers::sys::os::mac
{
class SysInfoImpl : public ::libs::helpers::sys::ISysInfo
{
  public:
  virtual ~SysInfoImpl ();

  virtual std::string  get (const TypeInfo& type) const override;
  virtual std::int16_t count_cpu () const override;


  private:
  mutable cpu::CpuInfo helper_;   //<
};
}   // namespace libs::helpers::sys::os::mac
#endif
