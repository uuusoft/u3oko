#pragma once
/**
\file       sys-info-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#ifdef U3_OS_ANDROID

namespace libs::helpers::sys::os::android
{
class SysInfoImpl : public ::libs::helpers::sys::ISysInfo
{
  public:
  virtual ~SysInfoImpl ();

  virtual std::string  get (const TypeInfo& type) const override;
  virtual std::int16_t count_cpu () const override;

  private:
  mutable cpu::CpuInfo helper_;
};
}   // namespace libs::helpers::sys::os::android

#endif
