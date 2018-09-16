#pragma once
/**
\file       x86cpu_id.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
//old shit
namespace libs { namespace helpers { namespace sys { namespace cpu { namespace x86 {
#if 0
  /**
  \brief  empty brief
  */
  inline
  tstring get_id()
  {
    tstring           _ret;
    low_cpu::CpuInfo  _helper;

    _helper.full_text( _ret );
    UASSERT( !_ret.empty() );
    return _ret;
  }
  /**
  \brief  empty brief
  */
  inline
  tstring get_speed()
  {
    return tstring( _T("???") );
  }
#endif

}}}}}      // namespace libs::helpers::sys::cpu::x86
