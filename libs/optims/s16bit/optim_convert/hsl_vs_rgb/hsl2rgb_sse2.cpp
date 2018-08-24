//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       hsl2rgb_sse2.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

UUU_SET_TARGET_CPU (sse2)
void
hsl_to_rgb24_sse2 (::libs::optim::MCallInfo& _info)
{
  XULOG_TRACE ("hsl_to_rgb24_sse2::beg");

  UASSERT_SIGNAL_OPTIM;

#if defined(UUU_CPU_X86_64)
  return hsl_to_rgb24_alu (_info);
#else
  return hsl_to_rgb24_sse1 (_info);
#endif

  XULOG_TRACE ("hsl_to_rgb24_sse2::end");
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
