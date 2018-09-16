#pragma once
/**
\file       system-win32-property.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief    
*/

namespace libs { namespace iproperties { namespace vers { namespace system {
/**
\brief  empty brief
*/
class SystemWin32Property final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (SystemWin32Property);

  SystemWin32Property ()
  {}

  virtual ~SystemWin32Property ()
  {}

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

}}}}      // namespace libs::iproperties::vers::system
