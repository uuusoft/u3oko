#pragma once
/**
\file       sys-info-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)

namespace libs::helpers::sys::os::linux
{
class SysInfoImpl : public ::libs::helpers::sys::ISysInfo
{
  public:
  virtual ~SysInfoImpl ();

  virtual std::string  get (const TypeInfo& type) const override;
  virtual std::int16_t count_cpu () const override;

  private:
  mutable cpu::CpuInfo helper_;   //< ???
};
}   // namespace libs::helpers::sys::os::linux

#endif
