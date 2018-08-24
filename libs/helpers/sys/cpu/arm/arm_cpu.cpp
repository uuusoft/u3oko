//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       arm_cpu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "arm_cpu.hpp"

namespace libs { namespace helpers { namespace sys { namespace cpu { namespace arm {

#if defined(UUU_CPU_ARM)

std::string
get_text_about_cpu ()
{
  //debug
  std::string _ret = "test text cpu arm";
  UASSERT (!_ret.empty ());
  return _ret;
}


bool
get_exts_cpu (SupportExtensionCPU& _ret)
{
  _ret.set (TypeExtCpu::neon);
  return true;
}


bool
get_all_info_cpu (SupportExtensionCPU& _ret)
{
  _ret.reset ();
  CHECK_CALL_NO_THROW (get_exts_cpu (_ret));

  _ret.id_cpu_ = get_text_about_cpu ();
  return true;
}

#endif
}}}}}      // namespace libs::helpers::sys::cpu::arm
