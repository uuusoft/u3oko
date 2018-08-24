//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    27.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функция для конвертации L <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "rgb_to_l_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb {

UUU_SET_TARGET_CPU (avx)
void
rgb24_to_l_avx1 (::libs::optim::MCallInfo& _info)
{
  _mm256_zeroupper ();
  rgb24_to_l_sse2 (_info);
  _mm256_zeroupper ();
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
