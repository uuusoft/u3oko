#pragma once
/**
\file       sys-info-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace sys { namespace os { namespace win32 {
/**
  \brief  empty brief
  */
class SysInfoImpl : public ISysInfo
{
  public:
  virtual ~SysInfoImpl ();

  virtual std::string get (const TypeInfo& _type) const override;
  virtual short       count_cpu () const override;


  private:
  mutable cpu::CpuInfo helper_;      //< ???
};

}}}}}      // namespace libs::helpers::sys::os::win32
