#pragma once
/**
\file       sys-info-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace sys { namespace os { namespace lnux {

#if defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_RASPBERRY)
/**
  \brief  empty brief
  */
class SysInfoImpl : public ::libs::helpers::sys::ISysInfo
{
  public:
  virtual ~SysInfoImpl ();

  virtual std::string get (const TypeInfo& _type) const override;
  virtual short       count_cpu () const override;


  private:
  mutable cpu::CpuInfo helper_;      //<  ???
};
#endif

}}}}}      // namespace libs::helpers::sys::os::lnux
